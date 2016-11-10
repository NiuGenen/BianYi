//#include<stdio.h>
//#include<stdlib.h>
//#include<string.h>
//
//void printStr(char *s) {
//	printf( "STRING: " );
//	int i = 0;
//	while (s[i]!='\0') {
//		printf("%c", s[i]);
//		++i;
//	}
//	printf( "\\0\n" );
//}
//
////int main() 
////{
////	int strLen = 8;
////	char *str = (char *)malloc(sizeof(char) * (strLen + 1));
////	memset(str, 0, (strLen + 1) * sizeof(char));
////
////	char *str2 = "hello";
////	printf("STR2: %s\n", str2);
////
////	int Len = strlen(str2);
////	printf("Len: %d\n", Len);
////
////	strcpy_s(str, strLen,str2);
////	printf("STR: %s\n", str);
////
////	free(str);
////	str = (char *)malloc(sizeof(char) * (strLen - 1));
////	strcpy_s(str, strLen, str2);
////	printf("STR: %s\n", str);
////
////	system("pause");
////	return 0;
////}
//
//int main() 
//{
//	int a = 1;
//	int b = 2;
//	//printf("a++1 = %d\n", a++1);//错误，不识别为“a+ +1”而是“a++ 1”，故语法错误
//	printf("a+ +1 = %d\n", a + +1);//正确，识别为“a+ +1”
//	//printf("a++1 = %d\n", a++b);//错误，不识别为“a+ +b”而是“a++ b”，故语法错误
//	printf("a+ +b = %d\n", a + +b);//正确，识别为“a+ +b”
//
//	system("pause");
//	return 0;
//}