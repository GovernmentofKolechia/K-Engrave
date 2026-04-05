<img width="546" height="813" alt="image" src="https://github.com/user-attachments/assets/fe28c315-eb06-4dcb-bbc3-6990cc4d6654" />

This is K-Engrave,
A tool where you can control your SystemD Jobs easily without commands such as:


systemctl stop "job"
systemctl restart "job"
systemctl start "job"
systemctl status

And More.

Why this tool? Becuase humans also need a break from typing in commands for SystemD and everyone hates it.
But Arch still uses it so, I guess there are still people that use it.
So, Why not just make a GUI for this?

/// INSTALLATION ///
1. Download this repository
2. CD into the folder.

cd k-engrave

3. CD into the build folder

cd build

4. CLEAR THE PREVIOUS BUILD FILES.

rm -rf * // EXECUTE THIS INSIDE THE BUILD FILE

5. MAKE YOUR OWN CONFIGURATION FOR "MAKE"

cmake ..


6. Execute the "make" command to build K-Engrave
7. Execute the command to open the app!

./kengrave

After this, K-Engrave should open if no errors occured during the installation.
If you have any questions // ideas // errors,
Contact me:

the.kolechia.gov@gmail.com


EXECUTE THIS FOR THE NEEDED PACKAGES FOR K-ENGRAVE:
sudo pacman -S --needed base-devel cmake qt6-base qt6-declarative qt6-controls2 qt6-svg kirigami extra-cmake-modules kcoreaddons ki18n libdbus qt6-dbus hicolor-icon-theme breeze-icons

<img width="514" height="810" alt="image" src="https://github.com/user-attachments/assets/fe532b42-9828-489d-9f9e-1be891f578c3" />
