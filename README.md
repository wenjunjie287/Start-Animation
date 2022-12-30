# Start-Animation
//启动界面

外部调用exe
    QProcess * process = new QProcess;
    process->setWorkingDirectory("./");
    process->start("./StartSurface.exe /settings/images/Scan.gif 1000 120 120");
    //process->start("./tartSurface.exe /res/png 1000 500 500");
	  //命令行参数格式
    /*
        可执行文件的路径 图片(或者目录)路径 间隔时间(ms)  gif  只能为文件
        当第二个参数是一个目录时可选择传入第三个参数"间隔时间"，及切换图片的时间，默认为30ms
    */