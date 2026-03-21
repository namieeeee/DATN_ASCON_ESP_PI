var group__can__struct__define =
[
    [ "CAN_Init_T", "group__can__struct__define.html#structCAN__Init__T", [
      [ "mode", "group__can__struct__define.html#a6b29e4f37f4482274af785ad5ffe96a7", null ],
      [ "rx_overflow_mode", "group__can__struct__define.html#aee42c911e39e573aade1ac4ee7c9a91b", null ],
      [ "pre_scaler", "group__can__struct__define.html#a2b74dbb147899c23eda297b56cb039fc", null ],
      [ "sync_jump_width", "group__can__struct__define.html#a80d3fef88c12bdb77a927f9941c080ff", null ],
      [ "time_seg1", "group__can__struct__define.html#aaf73afa1ef6d949446fdabf7244fe89c", null ],
      [ "time_seg2", "group__can__struct__define.html#ac1ff3090bfb98a405852e8679d96868e", null ],
      [ "transmit_fifo_priority", "group__can__struct__define.html#a74ac6aa0cf758db8bd541fe498722c5c", null ],
      [ "auto_retransmission", "group__can__struct__define.html#ade5028baa38e481dd9bcb3af457074fb", null ],
      [ "self_ack", "group__can__struct__define.html#ae18979b82496eba5b114556a4caa856a", null ]
    ] ],
    [ "CAN_Filter_T", "group__can__struct__define.html#structCAN__Filter__T", [
      [ "filter_code", "group__can__struct__define.html#adc3c2561b63a35daf5281b2863c08dad", null ],
      [ "filter_mask", "group__can__struct__define.html#a5e0f7fe381f665b3851bf30ef950a44e", null ],
      [ "filter_scale", "group__can__struct__define.html#a76bdd7aeca8751a4d5af02c18a33ae57", null ],
      [ "filter_activation", "group__can__struct__define.html#a0a1203fed9d434b3a19b0fb7265c7508", null ],
      [ "filter_index", "group__can__struct__define.html#a3c373e4f03062369dbd344d86b35853b", null ]
    ] ],
    [ "CAN_TxHeader_T", "group__can__struct__define.html#structCAN__TxHeader__T", [
      [ "id", "group__can__struct__define.html#abaabdc509cdaba7df9f56c6c76f3ae19", null ],
      [ "ide", "group__can__struct__define.html#a1335f6e71524c85fd1ccccda431ac32c", null ],
      [ "rtr", "group__can__struct__define.html#a1f32fc9e5d3b33babf5905140e7a53af", null ],
      [ "dlc", "group__can__struct__define.html#a811fbb0cb2c2263b1a7440a7e9d78239", null ]
    ] ],
    [ "CAN_RxHeader_T", "group__can__struct__define.html#structCAN__RxHeader__T", [
      [ "id", "group__can__struct__define.html#abaabdc509cdaba7df9f56c6c76f3ae19", null ],
      [ "ide", "group__can__struct__define.html#a1335f6e71524c85fd1ccccda431ac32c", null ],
      [ "rtr", "group__can__struct__define.html#a1f32fc9e5d3b33babf5905140e7a53af", null ],
      [ "dlc", "group__can__struct__define.html#a811fbb0cb2c2263b1a7440a7e9d78239", null ],
      [ "timestamp", "group__can__struct__define.html#ab20b0c7772544cf5d318507f34231fbe", null ]
    ] ],
    [ "CAN_Handle_T", "group__can__struct__define.html#structCAN__Handle__T", [
      [ "instance", "group__can__struct__define.html#aa944457f86dcf182a971ebd809a2caff", null ],
      [ "init", "group__can__struct__define.html#a46c6643459901eac00de98741be81e67", null ],
      [ "mutex", "group__can__struct__define.html#a0dc4dac3d1a6620c0fe26bcd57fd1de3", null ],
      [ "state", "group__can__struct__define.html#ae5a70e1eb6c9e7e1f74814d0e11c4e05", null ],
      [ "state_ex", "group__can__struct__define.html#acc2c472b9f3ba6450db01e11c49b921d", null ],
      [ "error_code", "group__can__struct__define.html#a81f6866795ba9ccef69d50e605bea468", null ],
      [ "notification", "group__can__struct__define.html#aa0fdd896a6d7826a4206dc7b3daf0ba1", null ]
    ] ],
    [ "CAN_Callback_T", "group__can__struct__define.html#ga8cafd3994a4c0b8639de37d2fbf3b964", null ],
    [ "CAN_CallbackID_T", "group__can__struct__define.html#gae26643891318704de4f0c3d3d3d1fe7b", [
      [ "HAL_CAN_TX_PTB_CPLT_CB_ID", "group__can__struct__define.html#ggae26643891318704de4f0c3d3d3d1fe7ba47f75fd1a2d126b57ff03e0a409c461c", null ],
      [ "HAL_CAN_TX_STB_CPLT_CB_ID", "group__can__struct__define.html#ggae26643891318704de4f0c3d3d3d1fe7baa3a020c1cae7b0dd2be76d6a902b03b9", null ],
      [ "HAL_CAN_TX_ABORT_CB_ID", "group__can__struct__define.html#ggae26643891318704de4f0c3d3d3d1fe7ba3af5f5a839cb9bea1658b910dcb99743", null ],
      [ "HAL_CAN_RX_FIFO_ONE_CB_ID", "group__can__struct__define.html#ggae26643891318704de4f0c3d3d3d1fe7ba03b20b0b32f07f799135695d162b6915", null ],
      [ "HAL_CAN_RX_FIFO_HALF_CB_ID", "group__can__struct__define.html#ggae26643891318704de4f0c3d3d3d1fe7ba6986a7e48f25ae761493ed132b71c2a1", null ],
      [ "HAL_CAN_RX_FIFO_FULL_CB_ID", "group__can__struct__define.html#ggae26643891318704de4f0c3d3d3d1fe7ba41b0542a0a0e9cf326891fb3e6e6529c", null ],
      [ "HAL_CAN_ERROR_CB_ID", "group__can__struct__define.html#ggae26643891318704de4f0c3d3d3d1fe7bab0e567bf5e4423a43dd46befda336944", null ],
      [ "HAL_CAN_MSP_INIT_CB_ID", "group__can__struct__define.html#ggae26643891318704de4f0c3d3d3d1fe7ba30c3cdd55390024a7406dffd629b58e4", null ],
      [ "HAL_CAN_MSP_INIT_FILTER_CB_ID", "group__can__struct__define.html#ggae26643891318704de4f0c3d3d3d1fe7bab1f11cbe5795e5bfedc7537312c7d237", null ],
      [ "HAL_CAN_MSP_DEINIT_CB_ID", "group__can__struct__define.html#ggae26643891318704de4f0c3d3d3d1fe7ba83d866b79daaabe636d9aaef4a3b1a45", null ]
    ] ],
    [ "CAN_TX_STA_T", "group__can__struct__define.html#ga9e395ad4a9e31c0e3fe2257b032dc3bb", [
      [ "HAL_CAN_TX_EMPTY", "group__can__struct__define.html#gga9e395ad4a9e31c0e3fe2257b032dc3bba6986394dd0304c770fd9e5ec4f54f55a", null ],
      [ "HAL_CAN_TX_LESS_HALF", "group__can__struct__define.html#gga9e395ad4a9e31c0e3fe2257b032dc3bba78b3e4ca33cebef06d01726c3e6d21ce", null ],
      [ "HAL_CAN_TX_MORE_HALF", "group__can__struct__define.html#gga9e395ad4a9e31c0e3fe2257b032dc3bba68182a84e773e2bd5c313efbe3da06bc", null ],
      [ "HAL_CAN_TX_FULL", "group__can__struct__define.html#gga9e395ad4a9e31c0e3fe2257b032dc3bbab410a7eb4f84b6bd62ef71a810e7fd7e", null ]
    ] ],
    [ "CAN_RX_STA_T", "group__can__struct__define.html#ga5fc7800d69f0538dbb89bc6a056c6658", [
      [ "HAL_CAN_RX_EMPTY", "group__can__struct__define.html#gga5fc7800d69f0538dbb89bc6a056c6658a275b3ed9ed876d4da877433634ffa026", null ],
      [ "HAL_CAN_RX_LESS_HALF", "group__can__struct__define.html#gga5fc7800d69f0538dbb89bc6a056c6658a555909e7cdc6659a286eeedbfc1cc673", null ],
      [ "HAL_CAN_RX_MORE_HALF", "group__can__struct__define.html#gga5fc7800d69f0538dbb89bc6a056c6658a93ce21dfe5c068fdb830dc309ecd03d6", null ],
      [ "HAL_CAN_RX_FULL", "group__can__struct__define.html#gga5fc7800d69f0538dbb89bc6a056c6658a9afb6db4aecf98f150376540035efbc0", null ]
    ] ]
];