#include "pch.h"
#include "DatabaseControl.h"

DatabaseControl::DatabaseControl() : databaseConnection(_T("DSN=NWPProjekt")) {

}

bool DatabaseControl::OpenConnection() {
	if (this->database.OpenEx(this->databaseConnection) != 0) return true;
	return false;
}

void DatabaseControl::CloseConnection() {
	database.Close();
}

void DatabaseControl::ExecuteSQLCommand(CString statement) {
	database.ExecuteSQL(statement);
}
