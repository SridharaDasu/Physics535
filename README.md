Instructions for the use of Physics535 Exercises

   Your first step is to set up access to login.hep.wisc.edu conveniently. 
   
   We will use VNC to port linux desktop of login.hep.wisc.edu to your laptop 
   
   You will need to start VNC on the login.hep.wisc.edu. To do that:
   
   Open a Terminal emulator window on your laptop 
   
	(you can use putty on a Windows laptop or Terminal.app on a Mac laptop)
	
              ssh login.hep.wisc.edu

Note that login.hep.wisc.edu is a pseudonym for several machines - you will
be logged in to one of login01, login02, ... login06.
After logging in with your HEP password type:

              vncserver -geometry 1200x800

The 1200x800 is the screen size in pixel units and can be adjusted to suit your laptop
The first time you issue the above command, it will prompt for a password twice.
Use a simple password as it is not super-secure.  You need that to connect to the server.
The program prints out the name of the machine and number for the display.
In my case it printed:  login02.hep.wisc.edu and 1

You can then close the terminal window.  The server can remain active for extended
period of time across your work sessions.  If there is ever a problem, feel free to
kill the server:

	ssh login02.hep.wisc.edu
	vncserver -kill :1

You can then restart it as above.  It is important to go to your specific server
	
You will need a VNC client on your laptop.
   
        On a Mac laptop, I use Chicken : https://sourceforge.net/projects/chicken/
        
        On Windows laptop, I was told TightVNC works : http://www.tightvnc.com

Open up your VNC client program and use server name, display number and password you set above.
Once connected you should see the login.hep.wisc.edu linux desktop.

Use the linux Gnome desktop enviornment menu that is displayed: Applications/System Tools/Terminal
to open a terminal window, where you will do most of your work.

Here are some tutorials for you in case you are not quite familiar with Unix command line:

https://www.codecademy.com/learn/learn-the-command-line

http://www.tutorialspoint.com/unix/

http://cli.learncodethehardway.org/book/

Commands to issue after first login:

    git clone https://github.com/SridharaDasu/Physics535.git
    
    cd ~/Physics535
    
    source environment.sh

Everytime you login:

    cd ~/Physics535
    
    source environment.sh

You can use Linux tools to browse / edit files (Emacs and Kate) which
are accessible from the Applications/Accessories menu.  You can use
other applications as well.  If there are troubles accessing some
application or the other please email help@hep.wisc.edu.

Then look at README files in individual exercise directories for further instructions
