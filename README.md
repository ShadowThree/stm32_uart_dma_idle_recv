# stm32_uart_dma_idle_recv
stm32f302ve, usart1 recv by DMA mode with idle interrupt. Output LOG by RTT and uart3 by priority and color.

# 说明
1. stm32CubeMx 配置选项
<img width="570" alt="6c8f656012543274e44ce53fbe54b06" src="https://github.com/ShadowThree/stm32_uart_dma_idle_recv/assets/41199004/8308609b-63fb-4b21-a67a-a66a548dceaf">

上图中，`mode`有两个选项：

1. `Normal`表示`DMA`接收完成后，就停止接收，需要重新调用`HAL_UARTEx_ReceiveToIdle_DMA();`函数才能开始下一次接收；
2. `Circular`表示`DMA`持续接收，不会主动停止。当给定的缓存满了后，又从头开始覆盖之前的数据；

上图中的`fifo`功能，我理解就是以下两种情况下会使用：
1. `DMA`的源数据和目标数据宽度不匹配，比如来源是按字节计算的，而目标地址需要按字存储，就可以通过`FIFO`转接完成这个数据宽度匹配；
2. 为了减少`DMA`占用总线是总时长，比如需要从外设采集数据存储到内存，数据来源为字节，不使用`FIFO`时，每个字节`DMA`都要写一次内存；当使用`FIFO`时，可以暂时将采集的数据存储到`FIFO`中，等积累到指定`threshold`，一次性将之前累积的数据存储到内存；
