#include "ocilib.h"

void err_handler(OCI_Error *err){
	printf("Error ORA-%05i - MSG : %s\n", OCI_ErrorGetOCICode(err), OCI_ErrorGetString(err));
}

int main(){
	OCI_Connection *cn;
	OCI_Statement *st;
	OCI_Resultset *rs;

	if(!OCI_Initialize(err_handler, NULL, OCI_ENV_DEFAULT)){
		return EXIT_FAILURE;
	}

	cn = OCI_ConnectionCreate("CENTORA","testuser","dldpdlwl",OCI_SESSION_DEFAULT);

	if(cn == NULL){
		OCI_Error *err = OCI_GetLastError();
		printf("Error code : %d, ErrorMsg: %s \n",OCI_ErrorGetOCICode(err), OCI_ErrorGetString(err));
		OCI_ConnectionFree(cn);
		return -1;
	}
	else{
		printf("connect success! \n\n");
	}
/*
	printf("Server major    version : %i\n", OCI_GetServerMajorVersion(cn));
        printf("Server minor    version : %i\n", OCI_GetServerMinorVersion(cn));
        printf("Server revision version : %i\n\n", OCI_GetServerRevisionVersion(cn));
        printf("Connection      version : %i\n\n", OCI_GetVersionConnection(cn));
*/

	st = OCI_StatementCreate(cn);

	printf("select * from TEST : \n");
	OCI_ExecuteStmt(st,"select * from TEST");
	rs = OCI_GetResultset(st);

	while(OCI_FetchNext(rs)){
		printf("data 1: %d, data 2 : %d, data3 : %s\n",OCI_GetInt(rs,1),OCI_GetInt(rs,2),OCI_GetString(rs,3));
	}

	OCI_StatementFree(st);
	OCI_ConnectionFree(cn);
	OCI_Cleanup();
	return EXIT_SUCCESS;
}
