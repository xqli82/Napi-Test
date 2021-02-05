#include <iostream>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>

using namespace std;
#define I2C_FILE_NAME "/dev/i2c-1"
#define I2C_ADDR 0x3c
#define CONTROL_CMD 0x00
#define CONTROL_DATA 0x40

void oled_write_cmd(int fd,unsigned char control,unsigned char cmd){
    unsigned char buf[2]={control,cmd};
    int flag =write(fd,buf,2);
    if(flag<0){
        cout<<"write falied"<<endl;
    }else{
        cout<<"write success"<<endl;
    }
}

void oled_init(int i2c_file){
    oled_write_cmd(i2c_file,CONTROL_CMD,0xae);
    oled_write_cmd(i2c_file,CONTROL_CMD,0xd5);
    oled_write_cmd(i2c_file,CONTROL_CMD,0x80);
    oled_write_cmd(i2c_file,CONTROL_CMD,0xa8);
    oled_write_cmd(i2c_file,CONTROL_CMD,0x1f);
    oled_write_cmd(i2c_file,CONTROL_CMD,0xd3);
    oled_write_cmd(i2c_file,CONTROL_CMD,0x00);
    oled_write_cmd(i2c_file,CONTROL_CMD,0x40);
    oled_write_cmd(i2c_file,CONTROL_CMD,0x8d);
    oled_write_cmd(i2c_file,CONTROL_CMD,0x14);
    oled_write_cmd(i2c_file,CONTROL_CMD,0x20);
    oled_write_cmd(i2c_file,CONTROL_CMD,0x02);
    oled_write_cmd(i2c_file,CONTROL_CMD,0xa1);
    oled_write_cmd(i2c_file,CONTROL_CMD,0xc8);
    oled_write_cmd(i2c_file,CONTROL_CMD,0xda);
    oled_write_cmd(i2c_file,CONTROL_CMD,0x02);
    oled_write_cmd(i2c_file,CONTROL_CMD,0x81);
    oled_write_cmd(i2c_file,CONTROL_CMD,0x8f);
    oled_write_cmd(i2c_file,CONTROL_CMD,0xd9);
    oled_write_cmd(i2c_file,CONTROL_CMD,0xf1);
    oled_write_cmd(i2c_file,CONTROL_CMD,0xdb);
    oled_write_cmd(i2c_file,CONTROL_CMD,0x40);
    oled_write_cmd(i2c_file,CONTROL_CMD,0xa4);
    oled_write_cmd(i2c_file,CONTROL_CMD,0xa6);
    oled_write_cmd(i2c_file,CONTROL_CMD,0x2e);
    oled_write_cmd(i2c_file,CONTROL_CMD,0xaf);
}

int main(){
    int i2c_file;
    i2c_file = open(I2C_FILE_NAME,O_RDWR);
    if(i2c_file < 0){
        cout <<"unable to open i2c control file"<<endl;
        return -1;
    }
    
    cout <<"open-------"<<I2C_FILE_NAME<<"-----success"<<endl;
    cout <<"i2c_file:"<< i2c_file<<endl;

    int io_int= ioctl(i2c_file,I2C_SLAVE_FORCE,I2C_ADDR);
    if(io_int<0){
        cout << "ioctl failed"<<endl;
        return -1;
    }
    cout <<"ioctl:"<<io_int<<endl;

    oled_init(i2c_file);

    close(i2c_file);

    return 0;
}