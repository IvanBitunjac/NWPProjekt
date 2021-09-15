#include "pch.h"
#include "DatabaseControl.h"

DatabaseControl::DatabaseControl() : databaseConnection(_T("DSN=NWPProjekt")) {

}

bool DatabaseControl::OpenConnection() {
	return database.OpenEx(databaseConnection) != 0;
}

void DatabaseControl::CloseConnection() {
	database.Close();
}

void DatabaseControl::ExecuteSQLCommand(CString statement) {
	database.ExecuteSQL(statement);
}

DatabaseControl::~DatabaseControl() {
	CloseConnection();
}
