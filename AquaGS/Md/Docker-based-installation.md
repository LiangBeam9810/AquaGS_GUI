## Run AquaGS by **docker** (Windows/Linux/Mac)👍

According to the official [Docker installation tutorial](https://www.docker.com/get-started/), whether on Windows, Linux or Mac systems, docker installation is very simple.

❗️  Make sure the [Docker](https://www.docker.com/get-started/) is installed. Follow these steps

### 1. Pull the specified image for AquaGS

- **Run the following command to pull the specified image for AquaGS in the Shell (Windows) or Terminal (Mac/Linux) of the device on which the Docker is installed.**

  ```
  docker pull liangbeam/aquags
  ```

  >Windows:
    ![Windows demo](/AquaGS/Md/gif/PullAquaGSIamge.gif)

  >Mac:
    ![Mac demo](/AquaGS/Md/gif/PullAquaGSIamge_mac.gif)
- **Run the following command to create a container**

  ```
  docker run -d --name aquags-vnc -p 5901:22 -p 6080:80 -p 5902:5900 -e VNC_PASSWORD=1234  liangbeam/aquags
  ```

  >Windows:
    ![Windows demo](/AquaGS/Md/gif/CreatContainer.gif)

  >Mac:
    ![Mac demo](/AquaGS/Md/gif/CreatContainer_mac.gif)

  | Commands             | Explanation            |
  | -------------------- | ---------------------- |
  | --name aquags-vnc    | container name         |
  | -p 5901:22           | SSH port               |
  | -p 6080:80           | NOVNC port (for web)   |
  | -p 5902:5900         | VNC port               |
  | -e VNC_PASSWORD=1234 | VNC and NOVNC password |

---

### 2.  Enter the container by Web

- Enter the following in the browser.

  ```
  <ip>:6080
  ```

  > Replace  `<ip>`  with the ip for the device on which the Docker is installed.
  >

  Enter the password, then you can access the desktop for container in browser.

  >Windows:
    ![Alt Text](/AquaGS/Md/gif/EnterVNC.gif)

  >Mac:
    ![Get ip](/AquaGS/Md/gif/find_ip_mac.gif)
    ![Enter the VNC](/AquaGS/Md/gif/EnterVNC_mac.gif)

### 3.   Launch AquaGS

- AquaGS_GUI download to the desktop  (directory is `/root/Desktop/AquaGS_GUI_release/`).
  **You need to run it in that directory** by run the command on the Terminal(or **LXTerminal**).

  ```
  cd /root/Desktop/AquaGS_GUI_release/
  ./AquaGS_GUI
  ```

  ![Alt Text](/AquaGS/Md/gif/lanuchAquaGS.gif)
  **Do not contain Spaces (' ') in the output path**

Then enjoy AquaGS.😃
