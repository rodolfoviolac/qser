#! /bin/bash
INIT_PATH=/etc/init.d
INIT_FILE=init-pins.sh

chmod +x ./copy2Init
echo "Copying Init Pins to Init.d"
cp $INIT_FILE $INIT_PATH
echo "Permitions Init Pins"
chmod +x $INIT_PATH/$INIT_FILE
echo "Adding to Defaults"
update-rc.d $INIT_PATH/$INIT_FILE defaults
echo "Done Copying and Updating Pins 2 Init.d"