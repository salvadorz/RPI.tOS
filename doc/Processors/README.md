
## Processors

### BCM2836

The Broadcom chip used in the Raspberry Pi 2 Model B. The underlying architecture in BCM2836 is identical to [BCM2835](bcm2835-peripherals.pdf "BCM2835 ARM Peripherals"). The only significant difference is the removal of the ARM1176JZF-S processor and replacement with a quad-core Cortex-A7 cluster.

You should refer to:

* [BCM2836 ARM-local peripherals](bcm2836-peripherals.pdf "BCM2836 ARM-local peripherals")

* Cortex-A7 MPcore Processor Reference Manual

### BCM2837

This is the Broadcom chip used in the Raspberry Pi 3 Model B, later models of the Raspberry Pi 2 Model B, and the Raspberry Pi Compute Module 3. The underlying architecture of the BCM2837 is identical to the BCM2836. The only significant difference is the replacement of the ARMv7 quad core cluster with a quad-core ARM Cortex A53 (ARMv8) cluster.

The ARM cores run at 1.2GHz, making the device about 50% faster than the Raspberry Pi 2. The VideoCore IV runs at 400MHz.

Please refer to the following BCM2837 document for details on the ARM peripherals specification.

* [BCM2837 ARM-local peripherals](bcm2837-peripherals_v2-1.pdf "BCM2837 ARM-local peripherals")

* [Cortex-A53 MPCore Processor TRM](Arm-Cortex-A53_MPCore_Processor_TRM "Cortex-A53 MPCore Processor Technical Reference Manual")

### BCM2837B0

This is the Broadcom chip used in the Raspberry Pi 3 Models A+, B+, and the Raspberry Pi Compute Module 3+. The underlying architecture of the BCM2837B0 is identical to the BCM2837 chip used in other versions of the Raspberry Pi. The ARM core hardware is the same, only the frequency is rated higher.

The ARM cores are capable of running at up to 1.4GHz, making the 3B+/3A+ about 17% faster than the original Raspberry Pi 3. The VideoCore IV runs at 400MHz. The ARM core is 64-bit, while the VideoCore IV is 32-bit.

The BCM2837B0 chip is packaged slightly differently to the BCM2837, and most notably includes a heat spreader for better thermals. This allows higher clock frequencies, and more accurate monitoring and control of the chip’s temperature.

This [post on the Raspberry Pi](https://www.raspberrypi.com/news/raspberry-pi-3-model-bplus-sale-now-35/ "Raspberry Pi 3 Model B+ on sale now at $35") goes into further detail about the BCM2837B0 chip.

### BCM2711

This is the Broadcom chip used in the Raspberry Pi 4 Model B, the Raspberry Pi 400, and the Raspberry Pi Compute Module 4. The architecture of the BCM2711 is a considerable upgrade on that used by the SoCs in earlier Raspberry Pi models. It continues the quad-core CPU design of the BCM2837, but uses the more powerful ARM A72 core. It has a greatly improved GPU feature set with much faster input/output, due to the incorporation of a PCIe link that connects the USB 2 and USB 3 ports, and a natively attached Ethernet controller. It is also capable of addressing more memory than the SoCs used before.

The ARM cores are capable of running at up to 1.5 GHz, making the Raspberry Pi 4 about 50% faster than the Raspberry Pi 3B+. The new VideoCore VI 3D unit now runs at up to 500 MHz. The ARM cores are 64-bit, and while the VideoCore is 32-bit, there is a new Memory Management Unit, which means it can access more memory than previous versions.

The BCM2711 chip continues to use the heat spreading technology started with the BCM2837B0, which provides better thermal management.

*Processor*: Quad-core [Cortex-A72](https://en.wikipedia.org/wiki/ARM_Cortex-A72 "Wiki Cortex-A72") (ARM v8) 64-bit SoC @ 1.5 GHz.

*Memory*: Accesses up to 8GB LPDDR4-2400 SDRAM (depending on model)

*Caches*: 32kB data + 48kB instruction L1 cache per core. 1MB L2 cache.

*Multimedia*: H.265 (4Kp60 decode); H.264 (1080p60 decode, 1080p30 encode); OpenGL ES, 3.0 graphics

*I/O*: PCIe bus, onboard Ethernet port, 2 × DSI ports (only one exposed on Raspberry Pi 4B), 2 × CSI ports (only one exposed on Raspberry Pi 4B), up to 6 × I2C, up to 6 × UART (muxed with I2C), up to 6 × SPI (only five exposed on Raspberry Pi 4B), dual HDMI video output, composite video output.

* [BCM2711 ARM-local peripherals](bcm2711-peripherals.pdf "BCM2711 ARM-local peripherals")
