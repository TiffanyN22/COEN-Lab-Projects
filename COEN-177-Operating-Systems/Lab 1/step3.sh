# Name: Tiffany Nguyen
# Date: September 25, 2024
# Title: Lab 1 - Unix/Linux Commands and Basic Shell Programming
# Description: This program checks the user information and runs a loop to calculate the area of a
# rectangle given the height/width and the area of a circle given the radius until the user exits

echo Executing $0
echo $(/bin/ls | wc -l) files
wc -l $(/bin/ls)
echo "HOME="$HOME
echo "USER="$USER
echo "PATH="$PATH
echo "PWD="$PWD
echo "\$\$="$$
user=`whoami`
numusers=`who | wc -l`
pi=3.14
echo "Hi $user! There are $numusers users logged on."
if [ $user = "tnguyen26" ]
then
    echo "Now you can proceed!"
else
    echo "Check who logged in!"
    exit 1
fi
response="Yes"
while [ $response != "No" ]
do
    echo "Enter height of rectangle: "
    read height
    echo "Enter width of rectangle: "
    read width
    area=`expr $height \* $width`
    echo "The area of the rectangle is $area"
    echo "Would you like to repeat for another rectangle [Yes/No]?"
    read response
done
response="Yes"
while [ $response != "No" ]
do
    echo "Enter radius of circle: "
    read radius
    area=$(echo "scale=2;$pi*$radius*$radius" |bc)
    echo "The area of the circle is $area"
    echo "Would you like to repeat for another circle [Yes/No]?"
    read response
done
