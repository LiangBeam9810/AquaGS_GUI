# Install packages for R
### Automatic installation
- As user friendly tool,the Function of " install all  package for R in one click " has been integrated in AquaGS_GUI.A stable network connection  is still essential for Automatic installation.
  
Automatic installation works fine if the following dependent libraries are installed:
* libcurl (lme4 needs)
* openssl (sommer needs)
* CMake  (lmerTest needs)
* lnlopt (lme4 needs)
* libgit2 (bestNormalize needs)
  
**Make sure these dependency libraries are installed in your linux! ! !**   
- You'll see such like this in the window named "Information output log"  when you first use AquaGS GUI and haven't installed the extension pack for R in advance.This is  installing the required  packages automatically.

**Please be patient, this will only happen once the first time you use AquaGS.**
![Image](./Pasted%20image%2020211102151138.png)
![Image](./Pasted_image_20211027172213.png)
![Image](./Pasted%20image%2020211027184711.png)

- when the error occurs during automatic installation,you will see this. Then you have to install packages manually.
![Image](./Pasted%20image%2020211027173033.png)
---
## Manual installation
- Manual installation also works.You can install these packages manually if you want.

	 - The requirement List show here:

		| **package** |**version** |
		|---|---|
		| data.table |1.14.2 |
		| nadiv |2.171. |
		| BGLR|1.1.0 |
		| ggplot2 |3.3.6 |
		| bestNormalize |1.8.3 |
		| lmerTest |3.1.3 |
		| ASRgenomics |1.0.0 |
		| lme4 |1.1.30|

---
### Notice 
Some solutions to the errors during installation are summarize [**here**](./errors_in_installing.md).