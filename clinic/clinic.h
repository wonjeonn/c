#ifndef CLINIC_H
#define CLINIC_H

// Formatting options
#define FMT_FORM 1
#define FMT_TABLE 2

// Array sizes
#define NAME_LEN 15
#define PHONE_DESC_LEN 4
#define PHONE_LEN 10
#define START_HOUR 10
#define END_HOUR 14
#define MINUTE_INTERVAL 30

// Structures
struct Phone {
    char description[PHONE_DESC_LEN + 1];
    char number[PHONE_LEN + 1];
};

struct Patient {
    int patientNumber;
    char name[NAME_LEN + 1];
    struct Phone phone;
};

struct Time {
    int hour;
    int min;
};

struct Date {
    int year;
    int month;
    int day;
};

struct Appointment {
    int patientNumber;
    struct Date date;
    struct Time time;
};

struct ClinicData {
    struct Patient* patients;
    int maxPatient;
    struct Appointment* appointments;
    int maxAppointments;
};

// Main: Entry-point
void menuMain(struct ClinicData* data);
void menuPatient(struct Patient patient[], int max);
void menuPatientEdit(struct Patient* patient);
void menuAppointment(struct ClinicData* data);

// Display
void displayPatientTableHeader(void);
void displayPatientData(const struct Patient* patient, int fmt);
void displayScheduleTableHeader(const struct Date* date, int isAllRecords);
void displayScheduleData(const struct Patient* patient,
                         const struct Appointment* appoint,
                         int includeDateField);
void displayAllPatients(const struct Patient patient[], int max, int fmt);
void searchPatientData(const struct Patient patient[], int max);
void addPatient(struct Patient patient[], int max);
void editPatient(struct Patient patient[], int max);
void removePatient(struct Patient patient[], int max);
void viewAllAppointments(struct ClinicData* data);
void viewAppointmentSchedule(struct ClinicData* data);

// Utility
void addAppointment(struct Appointment* appointments, int maxAppointments, struct Patient* patients, int maxPatients);
void removeAppointment(struct Appointment* appointments, int maxAppointments, struct Patient* patients, int maxPatients);
void searchPatientByPatientNumber(const struct Patient patient[], int max);
void searchPatientByPhoneNumber(const struct Patient patient[], int max);
int nextPatientNumber(const struct Patient patient[], int max);
int findPatientIndexByPatientNum(int patientNumber,
                                 const struct Patient patient[], int max);
void sort(struct Appointment* appointments, const int max);
int timeSlotAvailable(struct Date date, struct Time time, struct Appointment* appointment, int max);
int validAppointment(const int patientNumber, const struct Date date, const struct Appointment* appointment, const int max);

// User input
void inputPatient(struct Patient* patient);
void inputPhoneData(struct Phone* phone);
void validDate(struct Date* date);
void validTime(struct Time* time);

// File
int importPatients(const char* datafile, struct Patient patients[], int max);
int importAppointments(const char* datafile, struct Appointment appoints[], int max);

#endif
