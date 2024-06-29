#define PIC_MASTER_PORT1    0X20
#define PIC_MASTER_PORT2    0X21
#define PIC_SLAVE_PORT1     0xA0
#define PIC_SLAVE_PORT2     0xA1

#define PIC_IRQSTARTVECTOR  0x20

void kInitializePIC(void)
{
    // <Master PIC>
    kOutPortByte( PIC_MASTER_PORT1, 0x11);
    // ICW1: 
    // reserved        [7:4]=00X1 
    // Edge Trigger     [3](LTIM)=0
    // Use PIC Slave    [1](SNGL)=0
    // Use ICW4 Command [0](IC4)=1
    
    kOutPortByte( PIC_MASTER_PORT2, PIC_IRQSTARTVECTOR);
    // ICW2: 
    // PIC_MASTER Interupt vector offset = 0x20(32) (should be multiple of 8)
    // (0~31 is used by processor)

    kOutPortByte( PIC_MASTER_PORT2, 0x04);
    // ICW3: Slave PIC port in Mater PIC = 2 (0x04 = 2^2)
    
    kOutPortByte( PIC_MASTER_PORT2, 0x01);
    // ICW4: 
    // Not Using Special Fully Nested Mode [4] = 0, 
    // Not Using BufferMode [3]=0
    // Using Master PIC For BufferMode [2] = anyting
    // Disable Auto EOI [1] = 0
    // Use 8086/88 Mode [0]=1

    
    // <Slave PIC>
    kOutPortByte( PIC_SLAVE_PORT1, 0x11);
    // ICW1: 
    // reserved        [7:4]=00X1 
    // Edge Trigger     [3](LTIM)=0
    // Use PIC Slave    [1](SNGL)=0
    // Use ICW4 Command [0](IC4)=1
    kOutPortByte( PIC_SLAVE_PORT2, PIC_IRQSTARTVECTOR+0x08);
    // ICW2: 
    // PIC_SLAVE Interupt vector offset = 0x28(40) (should be multiple of 8)
    kOutPortByte( PIC_SLAVE_PORT2, 0x02);
    // ICW3: Slave PIC port in Mater PIC = 2 (0x02 = 2)
    
    kOutPortByte( PIC_SLAVE_PORT2, 0x01);
    // ICW4: 
    // Not Using Special Fully Nested Mode [4] = 0, 
    // Not Using BufferMode [3]=0
    // Using Slave PIC For BufferMode [2] = anyting
    // Disable Auto EOI [1] = 0
    // Use 8086/88 Mode [0]=1
}