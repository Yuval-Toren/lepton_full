#ifndef LEP_I2C_H_
#define LEP_I2C_H_

#define LEPTON_ADDRESS  (0x54)

#define POWER_REG (0x00)
#define STATUS_REG (0x02)
#define DATA_CRC_REG (0x28)

#define COMMANDID_REG (0x04)
#define DATALEN_REG (0x06)
#define DATA0 (0x08)

#define AGC (0x01)
#define SYS (0x02)
#define VID (0x03)
#define OEM (0x48)

#define GET (0x00)
#define SET (0x01)
#define RUN (0x02)

#define PING                        (0x00 )
#define CAM_STATUS                  (0x04 )
#define FLIR_SERIAL_NUMBER          (0x08 )
#define CAM_UPTIME                  (0x0C )
#define AUX_TEMPERATURE_KELVIN      (0x10 )
#define FPA_TEMPERATURE_KELVIN      (0x14 )
#define TELEMETRY_ENABLE_STATE      (0x18 )
#define TELEMETRY_LOCATION          (0x1C )
#define EXECTUE_FRAME_AVERAGE       (0x20 )
#define NUM_FRAMES_TO_AVERAGE       (0x24 )
#define CUST_SERIAL_NUMBER          (0x28 )
#define SCENE_STATISTICS            (0x2C )
#define SCENE_ROI                   (0x30 )
#define THERMAL_SHUTDOWN_COUNT      (0x34 )
#define SHUTTER_POSITION            (0x38 )
#define FFC_SHUTTER_MODE_OBJ        (0x3C )
#define RUN_FFC                     (0x42 )
#define FFC_STATUS                  (0x44 )

void lepton_command(unsigned int moduleID, unsigned int commandID, unsigned int command);
void set_reg(unsigned int reg);
int read_reg(unsigned int reg);
int read_metric_data();
void metric_enable();
void tresh();


#endif
