var group__i2c__struct__define =
[
    [ "I2C_Init_T", "group__i2c__struct__define.html#structI2C__Init__T", [
      [ "clock_speed", "group__i2c__struct__define.html#a6b31cd786761f86279de4b3a2c3d839f", null ],
      [ "own_address", "group__i2c__struct__define.html#a8c8307839e04067d4049e4a5d9fef8d4", null ],
      [ "addressing_mode", "group__i2c__struct__define.html#ad826b05efb4fda3f193a93728c3e17f4", null ],
      [ "gc_en", "group__i2c__struct__define.html#ae64aa0bee9a8cc0825e87b5b9e070782", null ]
    ] ],
    [ "I2C_Burst_T", "group__i2c__struct__define.html#structI2C__Burst__T", [
      [ "index1", "group__i2c__struct__define.html#ab99df7f0bc40f1e6f1bbc15f804752c4", null ],
      [ "index2", "group__i2c__struct__define.html#a1d346b76bea8c5967478058458188111", null ],
      [ "index2_en", "group__i2c__struct__define.html#a94d4a779bd19bc9c5c39baed495e8e8f", null ]
    ] ],
    [ "I2C_Handle_T", "group__i2c__struct__define.html#structI2C__Handle__T", [
      [ "instance", "group__i2c__struct__define.html#a4e017dfd8f605e9eb5e7cedb01d9d0a9", null ],
      [ "init", "group__i2c__struct__define.html#af375af8ea5aa76566bcff9d612583090", null ],
      [ "mutex", "group__i2c__struct__define.html#a0dc4dac3d1a6620c0fe26bcd57fd1de3", null ],
      [ "state", "group__i2c__struct__define.html#ae5a70e1eb6c9e7e1f74814d0e11c4e05", null ],
      [ "mode", "group__i2c__struct__define.html#a5584dd107fb5749147117917f9b7392c", null ],
      [ "error_code", "group__i2c__struct__define.html#a81f6866795ba9ccef69d50e605bea468", null ],
      [ "buffer_ptr", "group__i2c__struct__define.html#a0cd08ea1a437f98acc891aef6716c66f", null ],
      [ "xfer_size", "group__i2c__struct__define.html#affbd205fcfce594389d0128e03d71011", null ],
      [ "xfer_count", "group__i2c__struct__define.html#a9b776c8c7e0fda5621154bfacecc4595", null ],
      [ "direction", "group__i2c__struct__define.html#a796888b51c78979af0c6fcaf76cc2fa8", null ],
      [ "own_address", "group__i2c__struct__define.html#aea9bc349fc18d2d05513f4a60b3c1a6f", null ],
      [ "dev_address", "group__i2c__struct__define.html#a5d73539aafcda67ade7da9056439d209", null ],
      [ "xfer_option", "group__i2c__struct__define.html#a55b2d4d77dcd9dd68b101d0150031c9d", null ],
      [ "xfer_state", "group__i2c__struct__define.html#acc39a622b60ea119c7929e350104b167", null ],
      [ "abort", "group__i2c__struct__define.html#a05c772979887f46588c0a4626bd89f64", null ],
      [ "ext_xfer", "group__i2c__struct__define.html#a550a48bd62efcade8fe26bd44a1fc5ae", null ]
    ] ],
    [ "I2C_Mode_T", "group__i2c__struct__define.html#ga79621cb0b22a08cc259b19f62807f6a7", [
      [ "HAL_I2C_MODE_NONE", "group__i2c__struct__define.html#gga79621cb0b22a08cc259b19f62807f6a7a98c8fd642b7ac45a23479bd597fc7a71", null ],
      [ "HAL_I2C_MODE_MASTER", "group__i2c__struct__define.html#gga79621cb0b22a08cc259b19f62807f6a7a1eea98660a170dd7b191c9dfe46da6d2", null ],
      [ "HAL_I2C_MODE_SLAVE", "group__i2c__struct__define.html#gga79621cb0b22a08cc259b19f62807f6a7a817358d19d278261f2047a5ec8ec6b53", null ]
    ] ],
    [ "HAL_I2C_CallbackID_T", "group__i2c__struct__define.html#gadc7e9ffdab69ba03847b9254acaf1f71", [
      [ "HAL_I2C_MASTER_TX_COMPLETE_CB_ID", "group__i2c__struct__define.html#ggadc7e9ffdab69ba03847b9254acaf1f71a0c827ab2e5f64ad636d791f5fb8833fe", null ],
      [ "HAL_I2C_MASTER_RX_COMPLETE_CB_ID", "group__i2c__struct__define.html#ggadc7e9ffdab69ba03847b9254acaf1f71a1e1f0a9a138201b4afad1ba7b886353f", null ],
      [ "HAL_I2C_SLAVE_TX_COMPLETE_CB_ID", "group__i2c__struct__define.html#ggadc7e9ffdab69ba03847b9254acaf1f71a9ff4dcf408400ac4477b59e6f8f90d25", null ],
      [ "HAL_I2C_SLAVE_RX_COMPLETE_CB_ID", "group__i2c__struct__define.html#ggadc7e9ffdab69ba03847b9254acaf1f71ab7044545bc20ae0f29245065cefaef02", null ],
      [ "HAL_I2C_ABORT_CB_ID", "group__i2c__struct__define.html#ggadc7e9ffdab69ba03847b9254acaf1f71ad47ca04bf5ac94b89c68fe8fcc656d0c", null ],
      [ "HAL_I2C_ERROR_CB_ID", "group__i2c__struct__define.html#ggadc7e9ffdab69ba03847b9254acaf1f71a8151c294b18994802627c8e196eda1ef", null ],
      [ "HAL_I2C_MSPINIT_CB_ID", "group__i2c__struct__define.html#ggadc7e9ffdab69ba03847b9254acaf1f71a1078f5ac552d0138d6941d4cf48e6e91", null ],
      [ "HAL_I2C_MSPDEINIT_CB_ID", "group__i2c__struct__define.html#ggadc7e9ffdab69ba03847b9254acaf1f71a6b6a6817ea85a35d2f15187c6d459dac", null ]
    ] ]
];