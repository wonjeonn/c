# Veterinary Clinic Management System

This project is a C-based veterinary clinic management system to manage patient information and appointments.

## Features

- **Patient Management:** Add, edit, and remove patient records.
- **Appointment Management:** Schedule and remove appointments.
- **Import Data:** Import patient and appointment data from files.
- **View and Search:** View patient and appointment data and search for specific records.

## Usage

When running the program, a menu will be presented to choose different options for patient and appointment management.

- **Patient Management:**
  - Choose the "Patient Management" option from the main menu.
  - Options:
    - "View Patient Data": View all patient records.
    - "Search Patients": Search for patients by patient number or phone number.
    - "Add Patient": Add a new patient record.
    - "Edit Patient": Edit an existing patient record.
    - "Remove Patient": Remove a patient record.

- **Appointment Management:**
  - Choose the "Appointment Management" option from the main menu.
  - Options:
    - "View All Appointments": View all scheduled appointments.
    - "View Appointments by Date": View appointments for a specific date.
    - "Add Appointment": Schedule a new appointment.
    - "Remove Appointment": Remove an existing appointment.

## File Structure

- `main.c`: The main program file that orchestrates the clinic management system.
- `core.h` and `core.c`: Contains utility functions for input and data handling.
- `clinic.h` and `clinic.c`: Defines the data structures and functions for clinic management.
- `patientData.txt`: A file containing patient data that can be imported.
- `appointmentData.txt`: A file containing appointment data that can be imported.
