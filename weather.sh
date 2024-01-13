#!/bin/bash

# Path to the report file
DATA_FILE=~/Desktop/investigation/cew.1/environmental_report.txt

# Path to the complex executable
complex_EXEC=~/Desktop/investigation/cew.1/environment_program
while true; do
	# Run complex to update data
	$complex_EXEC

	# Function to read data from processed_data.txt
	read_data() {
	    if [ -f "$DATA_FILE" ]; then
		cat "$DATA_FILE"
	    else
		echo "No data available"
	    fi
	}

	# Read data from processed_data.txt
	data=$(read_data)

	# Display popup using Zenity
	zenity --info --text="$data" --width 500 --height 250 --timeout=10 --
	title="Environmental Data"
	    sleep 30
done
exit 0

