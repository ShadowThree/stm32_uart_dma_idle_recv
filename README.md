# stm32_uart_dma_idle_recv
stm32f302ve, usart1 recv by DMA mode with idle interrupt. Output LOG by RTT and uart3 by priority and color.

# 说明
1. stm32CubeMx 配置选项
<img width="570" alt="6c8f656012543274e44ce53fbe54b06" src="https://github.com/ShadowThree/stm32_uart_dma_idle_recv/assets/41199004/8308609b-63fb-4b21-a67a-a66a548dceaf">

上图中，`mode`有两个选项：

`Normal`表示`DMA`接收完成后，就停止接收，需要重新调用`HAL_UARTEx_ReceiveToIdle_DMA();`函数才能开始下一次接收；

`Circular`表示`DMA`持续接收，不会主动停止。当给定的缓存满了后，又从头开始覆盖之前的数据；
