//
// Created by 陈宇轩 on 2024/8/26.
//
#include<stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>
#include"Bmp.h"
#include"Lcd.h"
#include"touch.h"
#include <sys/types.h>
#include <dirent.h>
#define  viewpath "/home/cyx/view"

//int ret = execl("/usr/bin/mplayer",
//                "/usr/bin/mplayer",
//                "-slave",
//                "-quiet",
//                "-ao", "oss",                                    // 使用 OSS 音频驱动
//                "-vfm", "ffmpeg",                                // 使用 FFmpeg 视频解码器
//                "-lavdopts", "lowres=1:fast:skiploopfilter=all", // 解码优化选项
//                "-cache", "16384",                               // 设置缓存大小
//                "-autosync", "30",                               // 自动同步选项
//                "-msglevel",
//                "all=4", // 输出所有日志信息
//                "-input", "file=./fifo",
//                "-zoom", "-x", "700", "-y", "380",
//                "-geometry", "0:0",
//                mp4[0], // 要播放的文件的路径
//                NULL);



//创建管道文件
int create_fifo()
{

    //检测管道文件是否存在，不存在就创建
    int ret=access("./fifo",F_OK);
    {
        if(ret == 0)
        {
            printf("fifo has exist\n");
        }
        else if(ret == -1)
        {
            mkfifo("./fifo",0777); //创建管道文件
        }
    }

    int fifo_fd=open("./fifo",O_RDWR);  //打开管道文件
    if(fifo_fd == -1)
    {
        perror("open fifo failed");
        return -1;
    }

    return fifo_fd;
}

//把slave命令写入管道文件
int slave_write_cmd(int fifo_fd,char *cmd)
{
    write(fifo_fd,cmd,strlen(cmd));
    return 0;
}

//视频播放功能
int main()
{
    // 显示主界面
    Lcd_Init();
    BMP_Display("/home/cyx/buttom/black.bmp",0,0);
    BMP_Display("/home/cyx/buttom/V1.bmp", 20, 380);
    BMP_Display("/home/cyx/buttom/pre.bmp", 130, 380);
    BMP_Display("/home/cyx/buttom/back.bmp", 240, 380);
    BMP_Display("/home/cyx/buttom/stop.bmp", 350, 380);
    BMP_Display("/home/cyx/buttom/quck.bmp", 460, 380);
    BMP_Display("/home/cyx/buttom/next.bmp", 570, 380);
    BMP_Display("/home/cyx/buttom/V.bmp", 680, 380);

    int fifo_fd = create_fifo();
    int video_stop_cont_flags = 1;

    char mp4[12][42] ={0};
    int i = 0, j = 0;
    DIR *fd = opendir(viewpath);    //保存视频的目录
    if (fd == NULL)
        perror("opendir error");

    struct dirent *fp = NULL;
    struct stat st;

    while (fp = readdir(fd))
    {
        if (strcmp(fp->d_name, ".") == 0 || strcmp(fp->d_name, "..") == 0)
        {
            continue;
        }
        char pathname[512] = {0};
        sprintf(pathname, "%s/%s", viewpath, fp->d_name);
        if (stat(pathname, &st) == -1)
        {
            perror("stat error");
            continue;
        }

        strcpy(mp4[i], pathname);
        puts(mp4[i]);
        i++;
    }
    j = i-1;
    int max = i-1;
    closedir(fd);


    int play_flag = 0;
    pid_t pid;
    pid = fork(); // 创建进程

    if (pid == 0) // 子进程
    {
        while (1)
        {
            // 播放 1.mp4 视频
            int ret = execl("/usr/bin/mplayer",
                            "/usr/bin/mplayer",
                            "-slave",
                            "-quiet",
                            "-ao", "oss",                                    // 使用 OSS 音频驱动
                            "-vfm", "ffmpeg",                                // 使用 FFmpeg 视频解码器
                            "-lavdopts", "lowres=1:fast:skiploopfilter=all", // 解码优化选项
                            "-cache", "16384",                               // 设置缓存大小
                            "-autosync", "30",                               // 自动同步选项
                            "-msglevel",
                            "all=4", // 输出所有日志信息
                            "-input", "file=./fifo",
                            "-zoom", "-x", "800", "-y", "380",
                            "-geometry", "0:0",
                            mp4[1], // 要播放的文件的路径
                            NULL);
            if (ret == -1)
            {
                perror("errno execlp");
                // exit(1);
            }
        }
    }
    while (1) // 父进程
    {
        int vx = -1, vy = -1;
//        touch_wait(&vx, &vy);
        point p=Get_Point();
        vx=p.x,vy=p.y;
        // 视频播放
        if (vx >= 350 && vx <= 450 && vy >= 380 && vy <= 480)
        {
            if (play_flag == 0) // 当前是播放状态
            {
                BMP_Display("/home/cyx/buttom/start.bmp", 350, 380);
                kill(pid, SIGSTOP); // 子进程暂停
                play_flag = 1;
            }
            else
            {
                BMP_Display("/home/cyx/buttom/stop.bmp", 350, 380);
                kill(pid, SIGCONT); // 子进程继续
                play_flag = 0;
            }
        }

        // 视频退出
//        if (vx >= 700 && vx <= 800 && vy >= 0 && vy <= 380) // 点击空白处退出
//        {
//            kill(pid, SIGKILL);
//            // Show_Bmp(800, 480, 0, 0, "func.bmp");
//            close(fifo_fd);
//            break;
//        }

        // 播放上一个视频
        if (vx >= 130 && vx <= 230 && vy >= 380 && vy <= 480)
        {
            if (j == 0)
                j = max;
            else
                j--;
            // 杀死当前子进程
            kill(pid, SIGKILL);

            // 创建新的子进程去播放上一首
            pid = fork();
            if (pid == 0)
            {
                execl("/usr/bin/mplayer",
                      "/usr/bin/mplayer",
                      "-slave",
                      "-quiet",
                        //"-ao", "oss",                                    // 使用 OSS 音频驱动
                      "-vfm", "ffmpeg",                                // 使用 FFmpeg 视频解码器
                      "-lavdopts", "lowres=1:fast:skiploopfilter=all", // 解码优化选项
                      "-cache", "16384",                               // 设置缓存大小
                      "-autosync", "30",                               // 自动同步选项
                      "-msglevel",
                      "all=4", // 输出所有日志信息
                      "-input", "file=./fifo",
                      "-zoom", "-x", "800", "-y", "380",
                      "-geometry", "0:0",
                      mp4[j], // 要播放的文件的路径
                      NULL);
            }
        }

        // 播放下一个视频
        if (vx >= 570 && vx <= 670 && vy >= 380 && vy <= 480)
        {
            if (j == max)
                j = 0;
            else
                j++;
            // 杀死当前子进程
            kill(pid, SIGKILL);

            // 创建新的子进程去播放上一首
            pid = fork();
            if (pid == 0)
            {
                execl("/usr/bin/mplayer",
                      "/usr/bin/mplayer",
                      "-slave",
                      "-quiet",
                        //"-ao", "oss",                                    // 使用 OSS 音频驱动
                      "-vfm", "ffmpeg",                                // 使用 FFmpeg 视频解码器
                      "-lavdopts", "lowres=1:fast:skiploopfilter=all", // 解码优化选项
                      "-cache", "16384",                               // 设置缓存大小
                      "-autosync", "30",                               // 自动同步选项
                      "-msglevel",
                      "all=4", // 输出所有日志信息
                      "-input", "file=./fifo",
                      "-zoom", "-x", "800", "-y", "380",
                      "-geometry", "0:0",
                      mp4[j], // 要播放的文件的路径
                      NULL);
            }
        }

        // 视频快进
        if (vx >= 460 && vx <= 560 && vy >= 380 && vy <= 480)
        {
            slave_write_cmd(fifo_fd, "seek +5\n");
        }

        // 视频快退
        if (vx >= 240 && vx <= 340 && vy >= 380 && vy <= 480)
        {
            slave_write_cmd(fifo_fd, "seek -5\n");
        }

        // 音量增加
        if (vx >= 680 && vx <= 780 && vy >= 380 && vy <= 480)
        {
            slave_write_cmd(fifo_fd, "volume +200\n");
        }

        // 音量减少
        if (vx >= 20 && vx <= 120 && vy >= 380 && vy <= 480)
        {
            slave_write_cmd(fifo_fd, "volume -200\n");
        }
    }
}

