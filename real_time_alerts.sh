#!/bin/bash

# Function to display a pop-up with information from environmental_report.txt
show_popup() {
    local Temperature=$(awk -F': ' '/Temperature/ {print $2}' environmental_report.txt)
    if [ -n "$Temperature" ] && [ "$(echo "$Temperature < 25" | bc)" -eq 1 ]; then
        zenity --info --title="Environmental Alert" --text="Temperature is lower than 25: $Temperature" --timeout=3600
    fi
    elif [ "$(echo "$Temperature > 35" | bc)" -eq 1 ]; then
            zenity --info --title="Environmental Alert" --text="Temperature is higher than 35: $Temperature" --timeout=3600
        fi
}

# Function to execute environment_program in the background every 3 hours
run_environment_program() {
    while true; do 
        ./environment_program
        sleep 3600

    done
}

# Set up a real-time alert to trigger the show_popup function every 60 seconds
while true; do
    show_popup
    sleep 3600
done &

# Run the run_environment_program function in the background
run_environment_program &

# Keep the main script running
read -r -d '' _ </dev/null  # Keeps the script running