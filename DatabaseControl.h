#pragma once

#include "odbcinst.h"
#include "afxdb.h"


class DatabaseControl {
public:
	CDatabase database;
	CString databaseConnection;

public:

	DatabaseControl();
	//Opens DB connection through databaseConnection member
	bool OpenConnection();

	//Closes DB connection
	void CloseConnection();

	//For operations such as CREATE TABLE, INSERT, ALTER TABLE, DELETE etc.
	void ExecuteSQLCommand(CString statement);

	~DatabaseControl();
};