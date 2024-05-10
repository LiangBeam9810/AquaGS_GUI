## Run AquaGS by **docker** (Windows/Linux/Mac)👍

According to the official [Docker installation tutorial](https://www.docker.com/get-started/), whether on Windows, Linux or Mac systems, docker installation is very simple.

❗️  Make sure the [Docker](https://www.docker.com/get-started/) is installed. Follow these steps
- Here is the detailed [installation and operation demonstration video](https://www.youtube.com/watch?v=H4jV-lVUd5E) 
### 1. Pull and run the Docker for AquaGS

- **Open the Shell (Windows) or Terminal (Mac/Linux) of the device on which the Docker is installed.**

  - Windows: Press `Win + R`, type `cmd` and press `Enter`
  - Mac :    Press `Command + S` type `Terminal`, and press `Enter`.
  - Linux:   Press ` Ctrl + Alt + T` .
- **Run the following command  in the Shell (Windows) or Terminal (Mac/Linux).**

  ```
  docker pull liangbeam/aquags #Pull the specified image for AquaGS
  docker run -it -v d:\data\:/root/Desktop/Share/ -d --name aquags-vnc -p 5901:22 -p 6080:80 -p 5902:5900 -e VNC_PASSWORD=1234  liangbeam/aquags #Run the following command to create a container
  ```

  | Commands<br /> (Bold as can be customized) | Explanation                                                                | default                                                                   |
  | ------------------------------------------ | -------------------------------------------------------------------------- | ------------------------------------------------------------------------- |
  | -v **d:\\data** : **/home/data**    |  Share the host folder to the container | Share the host folder D:\data\ to the /root/Desktop/Share/ folder in the docker container |
  | -e VNC_PASSWORD=**1234**             | Password                                                                   | 1234                                                                      |
  | -p **6080**:80                        | NOVNC_port                                                                 | 6080                                                                      |
  | -p **5902**:5900                      | VNC port                                                                   | 5902                                                                      |
  | --name **aquags-vnc**                 | container name                                                             | aquags-vnc                                                                |
  | -p **5901**:22                        | SSH port                                                                   | 5901                                                                      |



If you get the following error:
```
  docker: Error response from daemon: user declined directory sharing 
```
You have to add your the folder path of the host (defult as  D:\data\\) to Docker Filesharing. Go to docker dashboard -> settings ->Resources -> FileSharing. Add required folder and hit Apply & Restart.

---

### 2.  Enter the container by Web

- Input the following IP address in the browser

  ```
  <your_ip>:<NOVNC_port> 
  ```

  > Replace  `<your_ip>`  with the ip for the device on which the Docker is installed.
  > Replace `<NOVNC_port> ` with `NOVNC_port` (default as 6080)
  >

  - **Exsample**: My local IP address is `<192.168.1.12>` , and the `NOVNC_port` is seted as default `6080`. So my input is `<192.168.1.12:6080>`

  Enter the password (default as 1234), then you can access the desktop for container in browser.

### 3.   Launch AquaGS

- AquaGS_GUI is already in `/root/Desktop/AquaGS_GUI_release/`.
  **You need to run it in that directory** by run the command on the Terminal(or **LXTerminal**).

  ```
  cd /root/Desktop/AquaGS_GUI_release/
  ./AquaGS_GUI
  ```

  ![Alt Text](/AquaGS/Md/gif/lanuchAquaGS.gif)
  **Do not contain Spaces (' ') in the output path**

Then enjoy AquaGS.😃

> Windows demo:
> ![Windows demo](/AquaGS/Md/gif/PullAquaGSIamge.gif)
> ![Windows demo](/AquaGS/Md/gif/CreatContainer.gif)

> Mac demo:
> ![Mac demo](/AquaGS/Md/gif/PullAquaGSIamge_mac.gif)
> ![Mac demo](/AquaGS/Md/gif/CreatContainer_mac.gif)

### Tips

Copy the host files/folders to the aquags-vnc container

```
  docker cp d:\data\ aquags-vnc:/home/data/
```
