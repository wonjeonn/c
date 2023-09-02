#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "core.h"
#include "clinic.h"

// Main: Entry-point
void menuMain(struct ClinicData* data) {
    int selection;

    do {
        printf("Veterinary Clinic System\n"
               "=========================\n"
               "1) PATIENT     Management\n"
               "2) APPOINTMENT Management\n"
               "-------------------------\n"
               "0) Exit System\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection) {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection) {
                printf("Exiting system... Goodbye.\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
            menuAppointment(data);
            break;
        }
    } while (selection);
}

void menuPatient(struct Patient patient[], int max) {
    int selection;

    do {
        printf("Patient Management\n"
               "=========================\n"
               "1) VIEW   Patient Data\n"
               "2) SEARCH Patients\n"
               "3) ADD    Patient\n"
               "4) EDIT   Patient\n"
               "5) REMOVE Patient\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection) {
        case 1:
            displayAllPatients(patient, max, FMT_TABLE);
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

void menuPatientEdit(struct Patient* patient) {
    int selection;

    do {
        printf("Edit Patient (%05d)\n"
               "=========================\n"
               "1) NAME : %s\n"
               "2) PHONE: ", patient->patientNumber, patient->name);

        displayFormattedPhone(patient->phone.number);

        printf("\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1) {
            printf("Name  : ");
            inputCString(patient->name, 1, NAME_LEN);
            putchar('\n');
            printf("Patient record updated!\n\n");
        } else if (selection == 2) {
            inputPhoneData(&patient->phone);
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}

void menuAppointment(struct ClinicData* data) {
    int selection;

    do {
        printf("Appointment Management\n"
               "==============================\n"
               "1) VIEW   ALL Appointments\n"
               "2) VIEW   Appointments by DATE\n"
               "3) ADD    Appointment\n"
               "4) REMOVE Appointment\n"
               "------------------------------\n"
               "0) Previous menu\n"
               "------------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection) {
        case 1:
            viewAllAppointments(data);
            suspend();
            break;
        case 2:
            viewAppointmentSchedule(data);
            suspend();
            break;
        case 3:
            addAppointment(data->appointments, data->maxAppointments,
                           data->patients, data->maxPatient);
            suspend();
            break;
        case 4:
            removeAppointment(data->appointments, data->maxAppointments,
                              data->patients, data->maxPatient);
            suspend();
            break;
        }
    } while (selection);
}

// Display
void displayPatientTableHeader(void) {
    printf("Pat.# Name            Phone#\n"
           "----- --------------- --------------------\n");
}

void displayPatientData(const struct Patient* patient, int fmt) {
    if (fmt == FMT_FORM) {
        printf("Name  : %s\n"
               "Number: %05d\n"
               "Phone : ", patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    } else {
        printf("%05d %-15s ", patient->patientNumber,
               patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}

void displayScheduleTableHeader(const struct Date* date, int isAllRecords) {
    printf("Clinic Appointments for the Date: ");

    if (isAllRecords) {
        printf("<ALL>\n\n");
        printf("Date       Time  Pat.# Name            Phone#\n"
               "---------- ----- ----- --------------- --------------------\n");
    } else {
        printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
        printf("Time  Pat.# Name            Phone#\n"
               "----- ----- --------------- --------------------\n");
    }
}

void displayScheduleData(const struct Patient* patient,
                         const struct Appointment* appoint,
                         int includeDateField) {
    if (includeDateField) {
        printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
               appoint->date.day);
    }
    
    printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.min,
           patient->patientNumber, patient->name);

    displayFormattedPhone(patient->phone.number);

    printf(" (%s)\n", patient->phone.description);
}

void displayAllPatients(const struct Patient patient[], int max, int fmt) {
    if (fmt == FMT_TABLE) {
        displayPatientTableHeader();
    }
    
    int i, count = 0;
    for (i = 0; i < max; i++) {
        if (patient[i].patientNumber != 0) {
            displayPatientData(&patient[i], fmt);
            count++;
        }
    }
    
    if (count == 0)
        printf("*** No records found ***\n");
    
    putchar('\n');
}

void searchPatientData(const struct Patient patient[], int max) {
    int selection;

    do {
        printf("Search Options\n"
               "==========================\n"
               "1) By patient number\n"
               "2) By phone number\n"
               "..........................\n"
               "0) Previous menu\n"
               "..........................\n"
               "Selection: ");

        selection = inputIntRange(0, 2);
        putchar('\n');
        
        switch (selection) {
            case 1:
                searchPatientByPatientNumber(patient, max);
                suspend();
                break;
            case 2:
                searchPatientByPhoneNumber(patient, max);
                suspend();
                break;
        }
    } while (selection);
}

void addPatient(struct Patient patient[], int max) {
    int i, count = 0;
    for (i = 0; i < max; i++) {
        if (patient[i].patientNumber == 0) {
            patient[i].patientNumber = nextPatientNumber(patient, max);
            inputPatient(&patient[i]);
            count++;
            printf("*** New patient record added ***\n");
            i = max;
        }
    }
    
    if (count == 0) {
        printf("ERROR: Patient listing is FULL!\n");
    }
    
    putchar('\n');
}

void editPatient(struct Patient patient[], int max) {
    printf("Enter the patient number: ");
    int patientNumber = inputIntPositive();
    putchar('\n');
    
    int index = findPatientIndexByPatientNum(patientNumber, patient, max);
    
    if (index >= 0) {
        menuPatientEdit(&patient[index]);
    } else {
        printf("ERROR: Patient record not found!\n");
    }
}

void removePatient(struct Patient patient[], int max) {
    printf("Enter the patient number: ");
    int patientNumber = inputIntPositive();
    putchar('\n');

    int index = findPatientIndexByPatientNum(patientNumber, patient, max);

    if (index >= 0) {
        displayPatientData(&patient[index], FMT_FORM);
        putchar('\n');
        
        printf("Are you sure you want to remove this patient record? (y/n): ");
        if (inputCharOption("yn") == 'y') {
            patient[index].patientNumber = 0;
            patient[index].name[0] = '\0';
            patient[index].phone.description[0] = '\0';
            patient[index].phone.number[0] = '\0';
            printf("Patient record has been removed!\n");
        } else {
            printf("Operation aborted.\n");
        }
    } else {
        printf("ERROR: Patient record not found!\n");
    }
    
    putchar('\n');
}

void viewAllAppointments(struct ClinicData* data) {
    sort(data->appointments, data->maxAppointments);
    
    displayScheduleTableHeader(NULL, 1);
    
    int i, j;
    for (i = 0; i < data->maxAppointments; i++) {
        for (j = 0; j < data->maxPatient; j++) {
            if (data->appointments[i].patientNumber && data->patients[j].patientNumber &&
                data->appointments[i].patientNumber == data->patients[j].patientNumber) {
                displayScheduleData(&data->patients[j], &data->appointments[i], 1);
            }
        }
    }
    
    putchar('\n');
}

void viewAppointmentSchedule(struct ClinicData* data) {
    struct Date date;
    validDate(&date);
    putchar('\n');
    
    sort(data->appointments, data->maxAppointments);
    
    displayScheduleTableHeader(&date, 0);
    int i, j;
    for (i = 0; i < data->maxAppointments; i++) {
        for (j = 0; j < data->maxPatient; j++) {
            if (data->appointments[i].patientNumber == data->patients[j].patientNumber &&
                data->appointments[i].date.year == date.year &&
                data->appointments[i].date.month == date.month &&
                data->appointments[i].date.day == date.day) {
                displayScheduleData(&data->patients[j], &data->appointments[i], 0);
            }
        }
    }
    
    putchar('\n');
}

// Utility
void addAppointment(struct Appointment* appointments, int maxAppointments, struct Patient* patients, int maxPatients) {
    struct Date date;
    struct Time time;

    int slotNotAvailable = 1;
    
    printf("Patient Number: ");
    int patientNumber = inputIntPositive();
    int index = findPatientIndexByPatientNum(patientNumber, patients, maxPatients);
    
    if (index >= 0) {
        while (slotNotAvailable) {
            validDate(&date);
            validTime(&time);
            putchar('\n');
            
            if (timeSlotAvailable(date, time, appointments, maxAppointments)) {
                printf("ERROR: Appointment timeslot is not available!\n\n");
            } else {
                appointments[index].date = date;
                appointments[index].time = time;
                appointments[index].patientNumber = patientNumber;
                printf("*** Appointment scheduled! ***\n");
                slotNotAvailable = 0;
            }
        }
    } else {
        printf("ERROR: Patient record not found!\n");
    }
    
    putchar('\n');
}

void removeAppointment(struct Appointment* appointments, int maxAppointments, struct Patient* patients, int maxPatients) {
    struct Date date;
     
    printf("Patient Number: ");
    int patientNumber = inputIntPositive();
    int index = findPatientIndexByPatientNum(patientNumber, patients, maxPatients);
    
    if (index < 0) {
        printf("ERROR: Patient record not found!\n");
    } else {
        validDate(&date);
        putchar('\n');
        
        int valid = validAppointment(patientNumber, date, appointments, maxAppointments);
        
        if (valid >= 0) {
            displayPatientData(&patients[index], FMT_FORM);
            printf("Are you sure you want to remove this appointment (y,n): ");
            if (inputCharOption("yn") == 'y') {
                appointments[valid].patientNumber = 0;
                appointments[valid].date.year = 0;
                appointments[valid].date.month = 0;
                appointments[valid].date.day = 0;
                appointments[valid].time.hour = 0;
                appointments[valid].time.min = 0;
                printf("\nAppointment record has been removed!\n");
            }
        } else {
            printf("ERROR: No appointment for this date!\n");
        }
    }
    
    putchar('\n');
}

void searchPatientByPatientNumber(const struct Patient patient[], int max) {
    printf("Search by patient number: ");
    int patientNumber = inputInt();
    putchar('\n');

    int index = findPatientIndexByPatientNum(patientNumber, patient, max);

    if (index != -1) {
        displayPatientData(&patient[index], FMT_FORM);
    } else {
        printf("*** No records found ***\n");
    }
    
    putchar('\n');
}

void searchPatientByPhoneNumber(const struct Patient patient[], int max) {
    char phoneNumber[PHONE_LEN + 1];

    printf("Search by phone number: ");
    inputCStringNum(phoneNumber, PHONE_LEN, PHONE_LEN);
    
    displayPatientTableHeader();
    
    int i, found = 0;
    for (i = 0; i < max; i++) {
        if (strcmp(patient[i].phone.number, phoneNumber) == 0) {
            displayPatientData(&patient[i], FMT_TABLE);
            found++;
        }
    }
    
    if (found == 0) {
        printf("*** No records found ***\n");
    }
    
    putchar('\n');
}

int nextPatientNumber(const struct Patient patient[], int max) {
    int i, maxNum = 0;
    for (i = 0; i < max; i++) {
        if (patient[i].patientNumber > maxNum) {
            maxNum = patient[i].patientNumber;
        }
    }

    return maxNum + 1;
}

int findPatientIndexByPatientNum(int patientNumber, const struct Patient patient[], int max) {
    int i;
    for (i = 0; i < max; i++) {
        if (patient[i].patientNumber == patientNumber) {
            return i;
        }
    }

    return -1;
}

void sort(struct Appointment* appointments, const int max) {
    int i, j;
    for (i = 0; i < max - 1; i++) {
        for (j = 0; j < max - i - 1; j++) {
            if (appointments[j].date.year > appointments[j + 1].date.year ||
               (appointments[j].date.year == appointments[j + 1].date.year &&
               (appointments[j].date.month > appointments[j + 1].date.month ||
               (appointments[j].date.month == appointments[j + 1].date.month &&
               (appointments[j].date.day > appointments[j + 1].date.day ||
               (appointments[j].date.day == appointments[j + 1].date.day &&
               (appointments[j].time.hour > appointments[j + 1].time.hour ||
               (appointments[j].time.hour == appointments[j + 1].time.hour &&
                appointments[j].time.min > appointments[j + 1].time.min)))))))) {
                struct Appointment temp = appointments[j];
                appointments[j] = appointments[j + 1];
                appointments[j + 1] = temp;
            }
        }
    }
}

int timeSlotAvailable(struct Date date, struct Time time, struct Appointment* appointment, int max) {
    int i, slotAvailable = 0;
    for (i = 0; i < max; i++) {
        if (date.year == appointment[i].date.year &&
            date.month == appointment[i].date.month &&
            date.day == appointment[i].date.day &&
            time.hour == appointment[i].time.hour
            && time.min == appointment[i].time.min) {
            slotAvailable = 1;
        }
    }

    return slotAvailable;
}

int validAppointment(const int patientNumber, const struct Date date, const struct Appointment* appointment, const int max) {
    int i, index = -1;
    for (i = 0; i < max; i++) {
        if ((appointment[i].patientNumber == patientNumber) &&
            (date.year == appointment[i].date.year) &&
            (date.month == appointment[i].date.month) &&
            (date.day == appointment[i].date.day)) {
            index = i;
            i = max;
        }
    }
    
    return index;
}

// User input
void inputPatient(struct Patient* patient) {
    printf("Patient Data Input\n"
           "------------------\n"
           "Number: %05d\n"
           "Name  : ", patient->patientNumber);

    inputCString(patient->name, 1, NAME_LEN);
    putchar('\n');
    
    inputPhoneData(&patient->phone);
}

void inputPhoneData(struct Phone* phone) {
    printf("Phone Information\n"
           "-----------------\n"
           "How will the patient like to be contacted?\n"
           "1. Cell\n"
           "2. Home\n"
           "3. Work\n"
           "4. TBD\n"
           "Selection: ");
    int selection = inputIntRange(1, PHONE_DESC_LEN);
    putchar('\n');

    switch (selection) {
        case 1:
            strcpy(phone->description, "CELL");
            break;

        case 2:
            strcpy(phone->description, "HOME");
            break;

        case 3:
            strcpy(phone->description, "WORK");
            break;

        case 4:
            strcpy(phone->description, "TBD");
            phone->number[0] = '\0';
            break;
    }

    if (selection != 4) {
        printf("Contact: %s\n"
               "Number : ", phone->description);
        inputCStringNum(phone->number, PHONE_LEN, PHONE_LEN);
    }
}

void validDate(struct Date* date) {
    int lastDay = 31;
    
    printf("Year        : ");
    date->year = inputIntPositive();
    printf("Month (1-12): ");
    date->month = inputIntRange(1, 12);

    if (date->month == 4 || date->month == 9 || date->month == 11) {
        lastDay = 30;
    }
    if (date->month == 2) {
        lastDay = 28;
        if ((date->year % 4 == 0 && date->year % 100 != 0) || (date->year % 400 == 0)) {
            lastDay = 29;
        }
    }

    printf("Day (1-%d)  : ", lastDay);
    date->day = inputIntRange(1, lastDay);
}

void validTime(struct Time* time) {
    int valid = 1;

    while (valid) {
        printf("Hour (0-23)  : ");
        time->hour = inputIntRange(0, 23);
        printf("Minute (0-59): ");
        time->min = inputIntRange(0, 59);
        
        if ((time->hour < START_HOUR || time->hour > END_HOUR) ||
            (time->hour == END_HOUR && time->min > 0) ||
            (time->min % MINUTE_INTERVAL != 0)) {
            printf("ERROR: Time must be between %02d:00 and %02d:00 in %d minute intervals.\n\n",
                   START_HOUR, END_HOUR, MINUTE_INTERVAL);
        } else {
            valid = 0;
        }
    }
}

// File
int importPatients(const char* datafile, struct Patient patients[], int max) {
    FILE* fp = NULL;
    fp = fopen(datafile, "r");

    int i = 0;
    if (fp != NULL) {
        while (i < max && fscanf(fp, "%d|%[^|]|%[^|]|%[^\n]",
            &patients[i].patientNumber,
            patients[i].name,
            patients[i].phone.description,
            patients[i].phone.number) != EOF) {
            i++;
        }
        
        fclose(fp);
    } else {
        printf("ERROR: File could not be read\n");
    }

    return i;
}

int importAppointments(const char* datafile, struct Appointment appoints[], int max) {
    FILE* fp = NULL;
    fp = fopen(datafile, "r");

    int i = 0;
    if (fp != NULL) {
        while (i < max && fscanf(fp, "%d,%d,%d,%d,%d,%d*c",
            &appoints[i].patientNumber,
            &appoints[i].date.year,
            &appoints[i].date.month,
            &appoints[i].date.day,
            &appoints[i].time.hour,
            &appoints[i].time.min) != EOF) {
            i++;
        }
               
        fclose(fp);
    }

    return i;
}
