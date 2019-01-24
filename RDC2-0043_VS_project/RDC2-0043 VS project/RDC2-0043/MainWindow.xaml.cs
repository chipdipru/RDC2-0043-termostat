/*
********************************************************************************
* COPYRIGHT(c) ЗАО «ЧИП и ДИП», 2018
* 
* Программное обеспечение предоставляется на условиях «как есть» (as is).
* При распространении указание автора обязательно.
********************************************************************************
*/


using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace RDC2_0043
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private const Int32 USB_PACKET_SIZE = 64;

        private const byte USB_REPORT_ID = 1;

        private const byte USB_CMD_POS = 1;
        private const byte USB_DATA_POS = 3;

        private const byte USB_CMD_EEPROM_WRITE = 0;
        private const byte USB_CMD_EEPROM_READ = 1;

        private const byte MODE_SIZE = 1;
        private const byte ACTIVE_LEVEL_SIZE = 1;
        private const byte THERMISTOR_R_NOMINAL_SIZE = 4;
        private const byte THERMISTOR_B_CONSTANT_SIZE = 2;
        private const byte TEMP_DELTA_LOW_SIZE = 2;
        private const byte TEMP_DELTA_HIGH_SIZE = TEMP_DELTA_LOW_SIZE;
        private const byte TEMP_NOMINAL_SIZE = 2;
        private const byte PROTECTION_ACTIVE_SIZE = 1;
        private const byte MAXIMUM_ON_TIME_SIZE = 2;

        private const byte MODE_OFFSET = 0;
        private const byte ACTIVE_LEVEL_OFFSET = (MODE_OFFSET + MODE_SIZE);
        private const byte THERMISTOR_R_NOMINAL_OFFSET = (ACTIVE_LEVEL_OFFSET + ACTIVE_LEVEL_SIZE);
        private const byte THERMISTOR_B_CONSTANT_OFFSET = (THERMISTOR_R_NOMINAL_OFFSET + THERMISTOR_R_NOMINAL_SIZE);
        private const byte TEMP_DELTA_LOW_OFFSET = (THERMISTOR_B_CONSTANT_OFFSET + THERMISTOR_B_CONSTANT_SIZE);
        private const byte TEMP_DELTA_HIGH_OFFSET = (TEMP_DELTA_LOW_OFFSET + TEMP_DELTA_LOW_SIZE);
        private const byte TEMP_NOMINAL_OFFSET = (TEMP_DELTA_HIGH_OFFSET + TEMP_DELTA_HIGH_SIZE);
        private const byte PROTECTION_ACTIVE_OFFSET = (TEMP_NOMINAL_OFFSET + TEMP_NOMINAL_SIZE);
        private const byte MAXIMUM_ON_TIME_OFFSET = (PROTECTION_ACTIVE_OFFSET + PROTECTION_ACTIVE_SIZE);

        private const byte PROTECTION_DISABLED = 0;
        private const byte PROTECTION_ENABLED = 1;
        private const UInt16 PROTECTION_MINUTE_MAX = 1500;
        private const UInt16 PROTECTION_MINUTE_MIN = 1;

        private static readonly string DeviceConnectedString = "Термостат RDC2-0043 подключен.";
        private static readonly string DeviceNotConnectedString = "Термостат RDC2-0043 не подключен. Подключите устройство и перезапустите программу.";
        
        public static readonly string[] OutLevelsStrings = { "0", "1", };

        private static readonly string UserInputErrorHeader = "Ошибка ввода данных";
        private static readonly string UserInputErrorCommonPhrase = "Неверно указан параметр: ";
        private static readonly string UserInputErrorTnom = "температура";
        private static readonly string UserInputErrordTH = "верхнее отклонение";
        private static readonly string UserInputErrordTL = "нижнее отклонение";
        private static readonly string UserInputErrorRnom = "номинальное сопротивление терморезистора";
        private static readonly string UserInputErrorBconst = "постоянная B терморезистора";
        private static readonly string UserInputErrorProtectTime = "время (от 1 до 1500 минут)";
        private static readonly string DownloadCommandHeader = "Загрузка конфигурации";
        private static readonly string DownloadCommandSuccess = "Загрузка выполнена";
        private static readonly string DownloadCommandError = "При загрузке возникла ошибка";
        private static readonly string OldFirmwareVersionHeader = "Доступна новая версия ПО устройства";
        private static readonly string OldFirmwareVersionMessage = "Настоятельно рекомендуется обновить ПО устройства.";
        private static readonly string FirmwareVersionPhrase = "Версия ПО устройства ";


        private const byte MODE_HEAT = 0;
        private const byte MODE_COOL = 1;
        private const float TEMP_FLOAT_TO_INT_VALUE = 10.0f;

        private const byte MINIMUM_FIRMWARE_VER = 0x20;


        public MainWindow()
        {
            InitializeComponent();

            OutLevelComboBox.ItemsSource = OutLevelsStrings;
            ModeImage.Source = new BitmapImage(new Uri("images/Mode_Heat.jpg", UriKind.Relative));

            Boolean USBDevDetected = USB_device.Open();

            ShowConnectionState(USBDevDetected);

            if (USBDevDetected)
            {
                byte[] USBPacket = new byte[USB_PACKET_SIZE];
                USBPacket[0] = USB_REPORT_ID;
                USBPacket[USB_CMD_POS] = USB_CMD_EEPROM_READ;                
                Boolean USBSuccess = USB_device.Write(USBPacket);
                
                USBSuccess = USB_device.Read(USBPacket);

                byte FirmwareVersion = USBPacket[USB_DATA_POS + MAXIMUM_ON_TIME_OFFSET + MAXIMUM_ON_TIME_SIZE];

                if (USBPacket[USB_DATA_POS + MODE_OFFSET] <= MODE_COOL)
                {
                    if (USBPacket[USB_DATA_POS + MODE_OFFSET] == MODE_HEAT)
                    {
                        HeatMode.IsChecked = true;
                        ModeImage.Source = new BitmapImage(new Uri("images/Mode_Heat.jpg", UriKind.Relative));
                    }
                        
                    else
                    {
                        CoolMode.IsChecked = true;
                        ModeImage.Source = new BitmapImage(new Uri("images/Cool_Heat.jpg", UriKind.Relative));
                    }
                        
                    Tnorm.Text = ((float)((USBPacket[USB_DATA_POS + TEMP_NOMINAL_OFFSET] | (USBPacket[USB_DATA_POS + TEMP_NOMINAL_OFFSET + 1] << 8)) / TEMP_FLOAT_TO_INT_VALUE)).ToString("f2");
                    dTH.Text = ((float)((USBPacket[USB_DATA_POS + TEMP_DELTA_HIGH_OFFSET] | (USBPacket[USB_DATA_POS + TEMP_DELTA_HIGH_OFFSET + 1] << 8)) / TEMP_FLOAT_TO_INT_VALUE)).ToString("f2");
                    dTL.Text = ((float)((USBPacket[USB_DATA_POS + TEMP_DELTA_LOW_OFFSET] | (USBPacket[USB_DATA_POS + TEMP_DELTA_LOW_OFFSET + 1] << 8)) / TEMP_FLOAT_TO_INT_VALUE)).ToString("f2");
                    OutLevelComboBox.SelectedIndex = USBPacket[USB_DATA_POS + ACTIVE_LEVEL_OFFSET];
                    RnomTextBox.Text = (USBPacket[USB_DATA_POS + THERMISTOR_R_NOMINAL_OFFSET] | (USBPacket[USB_DATA_POS + THERMISTOR_R_NOMINAL_OFFSET + 1] << 8) | (USBPacket[USB_DATA_POS + THERMISTOR_R_NOMINAL_OFFSET + 2] << 16) | (USBPacket[USB_DATA_POS + THERMISTOR_R_NOMINAL_OFFSET + 3] << 24)).ToString();
                    BconstTextBox.Text = (USBPacket[USB_DATA_POS + THERMISTOR_B_CONSTANT_OFFSET] | (USBPacket[USB_DATA_POS + THERMISTOR_B_CONSTANT_OFFSET + 1] << 8)).ToString();

                    if (FirmwareVersion >= MINIMUM_FIRMWARE_VER)
                    {                        
                        if (USBPacket[USB_DATA_POS + PROTECTION_ACTIVE_OFFSET] == PROTECTION_ENABLED)
                            ProtectionCheck.IsChecked = true;

                        ProtectionTimeTextBox.Text = (USBPacket[USB_DATA_POS + MAXIMUM_ON_TIME_OFFSET] | (USBPacket[USB_DATA_POS + MAXIMUM_ON_TIME_OFFSET + 1] << 8)).ToString();
                    }
                    else
                        ProtectionBorder.IsEnabled = false;
                }

                if (FirmwareVersion < MINIMUM_FIRMWARE_VER)
                    MessageBox.Show(OldFirmwareVersionMessage, OldFirmwareVersionHeader, MessageBoxButton.OK, MessageBoxImage.Exclamation);
                else
                    FirmwareTextBlock.Text = FirmwareVersionPhrase + (FirmwareVersion >> 4).ToString() + "." + (FirmwareVersion & 0x0F).ToString(); 
            }            
        }
        
        private void ShowConnectionState(bool State)
        {
            if (State)
            {
                StateImage.Source = new BitmapImage(new Uri("images/apply_32x32.png", UriKind.Relative));
                StateTextBlock.Text = DeviceConnectedString;
            }

            else
            {
                StateImage.Source = new BitmapImage(new Uri("images/warning_32x32.png", UriKind.Relative));
                StateTextBlock.Text = DeviceNotConnectedString;
            }
        }

        private void DownloadButton_Click(object sender, RoutedEventArgs e)
        {            
            byte[] USBPacket = new byte[USB_PACKET_SIZE];
            USBPacket[0] = USB_REPORT_ID;
            USBPacket[USB_CMD_POS] = USB_CMD_EEPROM_WRITE;
            
            if (HeatMode.IsChecked == true)
                USBPacket[USB_DATA_POS + MODE_OFFSET] = MODE_HEAT;
            else
                USBPacket[USB_DATA_POS + MODE_OFFSET] = MODE_COOL;

            Int16 IntSetValue = 0;

            if (TryParseStringToInt(Tnorm.Text, out IntSetValue))
            {
                USBPacket[USB_DATA_POS + TEMP_NOMINAL_OFFSET] = (byte)IntSetValue;
                USBPacket[USB_DATA_POS + TEMP_NOMINAL_OFFSET + 1] = (byte)(IntSetValue >> 8);
            }
            else
            {
                UserInputErrorMessage(UserInputErrorTnom);
                return;
            }

            if (TryParseStringToInt(dTH.Text, out IntSetValue))
            {
                USBPacket[USB_DATA_POS + TEMP_DELTA_HIGH_OFFSET] = (byte)IntSetValue;
                USBPacket[USB_DATA_POS + TEMP_DELTA_HIGH_OFFSET + 1] = (byte)(IntSetValue >> 8);
            }
            else
            {
                UserInputErrorMessage(UserInputErrordTH);
                return;
            }

            if (TryParseStringToInt(dTL.Text, out IntSetValue))
            {
                USBPacket[USB_DATA_POS + TEMP_DELTA_LOW_OFFSET] = (byte)IntSetValue;
                USBPacket[USB_DATA_POS + TEMP_DELTA_LOW_OFFSET + 1] = (byte)(IntSetValue >> 8);
            }
            else
            {
                UserInputErrorMessage(UserInputErrordTL);
                return;
            }

            USBPacket[USB_DATA_POS + ACTIVE_LEVEL_OFFSET] = (byte)OutLevelComboBox.SelectedIndex;

            UInt32 Uint32Val = 0;
            if (UInt32.TryParse(RnomTextBox.Text, out Uint32Val))
            {
                for (byte i = 0; i < THERMISTOR_R_NOMINAL_SIZE; i++)
                    USBPacket[USB_DATA_POS + THERMISTOR_R_NOMINAL_OFFSET + i] = (byte)(Uint32Val >> (8 * i));
            }
            else
            {
                UserInputErrorMessage(UserInputErrorRnom);
                return;
            }

            if (UInt32.TryParse(BconstTextBox.Text, out Uint32Val))
            {
                USBPacket[USB_DATA_POS + THERMISTOR_B_CONSTANT_OFFSET] = (byte)Uint32Val;
                USBPacket[USB_DATA_POS + THERMISTOR_B_CONSTANT_OFFSET + 1] = (byte)(Uint32Val >> 8);
            }
            else
            {
                UserInputErrorMessage(UserInputErrorBconst);
                return;
            }

            if (ProtectionCheck.IsChecked == true)
            {
                USBPacket[USB_DATA_POS + PROTECTION_ACTIVE_OFFSET] = PROTECTION_ENABLED;    
            }
            else
                USBPacket[USB_DATA_POS + PROTECTION_ACTIVE_OFFSET] = PROTECTION_DISABLED;

            if ((!UInt32.TryParse(ProtectionTimeTextBox.Text, out Uint32Val)) || (!((Uint32Val >= PROTECTION_MINUTE_MIN) && (Uint32Val <= PROTECTION_MINUTE_MAX))))
            {
                UserInputErrorMessage(UserInputErrorProtectTime);
                return;
            }
            else
            {
                USBPacket[USB_DATA_POS + MAXIMUM_ON_TIME_OFFSET] = (byte)Uint32Val;
                USBPacket[USB_DATA_POS + MAXIMUM_ON_TIME_OFFSET + 1] = (byte)(Uint32Val >> 8);
            }

            Boolean USBSuccess = USB_device.Write(USBPacket);
            if (USBSuccess)
                MessageBox.Show(DownloadCommandSuccess, DownloadCommandHeader, MessageBoxButton.OK, MessageBoxImage.Information);
            else
                MessageBox.Show(DownloadCommandError, DownloadCommandHeader, MessageBoxButton.OK, MessageBoxImage.Error);

            ShowConnectionState(USBSuccess);
        }

        void UserInputErrorMessage(string WrongSetting)
        {
            MessageBox.Show(UserInputErrorCommonPhrase + WrongSetting, UserInputErrorHeader, MessageBoxButton.OK, MessageBoxImage.Warning);            
        }

        private bool TryParseStringToInt(string Text, out Int16 IntValue)
        {
            bool Result = true;            
            float FloatValue;

            if (float.TryParse(Text, out FloatValue))
            {
                FloatValue *= 10;
                IntValue = (Int16)FloatValue;
            }

            else
            {
                IntValue = 0;
                Result = false;
            }
            return Result;
        }
        
        private void HeatMode_Clicked(object sender, RoutedEventArgs e)
        {
            ModeImage.Source = new BitmapImage(new Uri("images/Mode_Heat.jpg", UriKind.Relative));
        }

        private void CoolMode_Clicked(object sender, RoutedEventArgs e)
        {
            ModeImage.Source = new BitmapImage(new Uri("images/Mode_Cool.jpg", UriKind.Relative));
        }

        private void MainWindow_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            USB_device.Close();
        }
    }
}
