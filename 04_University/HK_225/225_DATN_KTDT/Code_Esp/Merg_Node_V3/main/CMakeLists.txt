# See the build system documentation in IDF programming guide
# for more information about component CMakeLists.txt files.

idf_component_register(
    SRCS main.c 
         decrypt.c 
         encrypt.c
         ascon.c
         dht22.c 
         DS3231.c 
         BH1750.c 
         LCD_I2C.c 

          # list the source files of this component
    INCLUDE_DIRS        # optional, add here public include directories
    PRIV_INCLUDE_DIRS   # optional, add here private include directories
    REQUIRES            # optional, list the public requirements (component names)
    PRIV_REQUIRES  driver esp_timer esp_rom freertos esp_driver_i2c   # optional, list the private requirements
)
