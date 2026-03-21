var group__eth__struct__define =
[
    [ "ETH_Init_T", "group__eth__struct__define.html#structETH__Init__T", [
      [ "AutoNegotiation", "group__eth__struct__define.html#aca914039c9b0088669b953a09695fbe3", null ],
      [ "Speed", "group__eth__struct__define.html#ad04b2041f59d32492ec36a891418f3fd", null ],
      [ "DuplexMode", "group__eth__struct__define.html#a7532a3f4add21e355c82b5b0a5de5b5c", null ],
      [ "PhyAddress", "group__eth__struct__define.html#a06b6f26d9590b5a3059119824b954d55", null ],
      [ "MACAddr", "group__eth__struct__define.html#a6eab7db71dca7c8d543246d32bf19834", null ],
      [ "RxMode", "group__eth__struct__define.html#a744fa34bf425d0c0a7d0c256eeb1041d", null ],
      [ "ChecksumMode", "group__eth__struct__define.html#a3109835a451377da573be18677070ec4", null ],
      [ "MediaInterface", "group__eth__struct__define.html#aed9c15857ee16b5c7a30b6c698425135", null ]
    ] ],
    [ "ETH_DMADescTypeDef", "group__eth__struct__define.html#structETH__DMADescTypeDef", [
      [ "StatusAndVDBC", "group__eth__struct__define.html#abc03e4dcbac8573abd7352478da6009d", null ],
      [ "StatusAndVLAN", "group__eth__struct__define.html#a244491d78035e3dcc9110efad5ae8f05", null ],
      [ "Buffer2NextDescAddr", "group__eth__struct__define.html#a5a6b97ad101110d3765e81ccd9a09b5c", null ],
      [ "Buffer1Addr", "group__eth__struct__define.html#a0ead65986ea5543acde032eefa8874aa", null ]
    ] ],
    [ "ETH_DMARxFrameInfos", "group__eth__struct__define.html#structETH__DMARxFrameInfos", [
      [ "FSRxDesc", "group__eth__struct__define.html#ae0713199379a4a1c6c3f74a776191380", null ],
      [ "LSRxDesc", "group__eth__struct__define.html#a66521e1e24956d24e89b2a7ec6af21c7", null ],
      [ "SegCount", "group__eth__struct__define.html#a1e83fcec73c28a1934ea39f370fce3a4", null ],
      [ "length", "group__eth__struct__define.html#aebb70c2aab3407a9f05334c47131a43b", null ],
      [ "buffer", "group__eth__struct__define.html#ac361fef6bf135953d536299eb0b119c3", null ]
    ] ],
    [ "ETH_PowerDownConfigTypeDef", "group__eth__struct__define.html#structETH__PowerDownConfigTypeDef", [
      [ "LinkDetect", "group__eth__struct__define.html#a8b445d2f652c74f118d10c84acd7f7a5", null ],
      [ "MagicPacket", "group__eth__struct__define.html#a57cd03e4dc10da11c7fcf27c158cfde0", null ],
      [ "WakeUpFrame", "group__eth__struct__define.html#a843e05d464ffc00975e9b26a8327a68c", null ],
      [ "WakeUpFrameMask", "group__eth__struct__define.html#aed8b4052fe941818b4b051977f2a1d8d", null ],
      [ "pFrame", "group__eth__struct__define.html#a009364f1c9cf5b59aeff6e3d285394d4", null ],
      [ "FrameSize", "group__eth__struct__define.html#a27e36977ca6bca242a08f1b9ede5203b", null ],
      [ "FrameNumber", "group__eth__struct__define.html#a751262eb52d313b56eb589c89160956c", null ]
    ] ],
    [ "ETH_WOLConfigTypeDef", "group__eth__struct__define.html#structETH__WOLConfigTypeDef", [
      [ "WakeUpPacket", "group__eth__struct__define.html#ad5d8c811f9d154e94caf0e99f4105687", null ],
      [ "MagicPacket", "group__eth__struct__define.html#a57cd03e4dc10da11c7fcf27c158cfde0", null ],
      [ "GlobalUnicast", "group__eth__struct__define.html#ae77b182557e9c61952f89ab68a7f965d", null ],
      [ "WakeUpForward", "group__eth__struct__define.html#a7957cc32bd0c9bb58c9deb19c004696c", null ]
    ] ],
    [ "ETH_Handle_T", "group__eth__struct__define.html#structETH__Handle__T", [
      [ "Instance", "group__eth__struct__define.html#a9336f81d61e25dd345f07459b32cf072", null ],
      [ "Init", "group__eth__struct__define.html#aa24c3ef226909de51ea60acf44df2e06", null ],
      [ "LinkStatus", "group__eth__struct__define.html#aad070cc8910a1bf8083ee8bb8eb07b43", null ],
      [ "RxDesc", "group__eth__struct__define.html#a74857352263f2d8cca2cfe7d0034c196", null ],
      [ "RxDMADescBaseAddr", "group__eth__struct__define.html#a7654616da66568d24dc80d71516bfde3", null ],
      [ "TxDesc", "group__eth__struct__define.html#ab694b40b75ee5797155621603afaba2d", null ],
      [ "TxDMADescBaseAddr", "group__eth__struct__define.html#ad35b6e9a38b5d99c40802f57c16458ab", null ],
      [ "RxFrameInfos", "group__eth__struct__define.html#a4e92450a6d127739c043ed3fe54f0963", null ],
      [ "State", "group__eth__struct__define.html#ae26118c6006f3ba49bf4bf823ca1eb55", null ]
    ] ],
    [ "HAL_ETH_CallbackIDTypeDef", "group__eth__struct__define.html#gaf5b4be2cf5c40468208d91219e67ac52", [
      [ "HAL_ETH_MSPINIT_CB_ID", "group__eth__struct__define.html#ggaf5b4be2cf5c40468208d91219e67ac52ac51721a58d0d76f28dc897ffb3992624", null ],
      [ "HAL_ETH_MSPDEINIT_CB_ID", "group__eth__struct__define.html#ggaf5b4be2cf5c40468208d91219e67ac52a74b7ff5dfee2f4adeb084a52b568189f", null ],
      [ "HAL_ETH_TX_COMPLETE_CB_ID", "group__eth__struct__define.html#ggaf5b4be2cf5c40468208d91219e67ac52ad81b87cf3fc9d3d0c7c29d52068cc168", null ],
      [ "HAL_ETH_RX_COMPLETE_CB_ID", "group__eth__struct__define.html#ggaf5b4be2cf5c40468208d91219e67ac52a420eaea0529e65d35a46c562791aaf95", null ],
      [ "HAL_ETH_DMA_ERROR_CB_ID", "group__eth__struct__define.html#ggaf5b4be2cf5c40468208d91219e67ac52adfe16a1a855490232d87f1f8b105c058", null ],
      [ "HAL_ETH_WAKEUP_CB_ID", "group__eth__struct__define.html#ggaf5b4be2cf5c40468208d91219e67ac52ada5b3cfb06bb5099b2a3266e4d846cc5", null ],
      [ "HAL_ETH_LINKCHG_CB_ID", "group__eth__struct__define.html#ggaf5b4be2cf5c40468208d91219e67ac52a2807ddc2d8339d9582bb25d97c25b008", null ]
    ] ]
];