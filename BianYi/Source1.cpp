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
//	//printf("a++1 = %d\n", a++1);//���󣬲�ʶ��Ϊ��a+ +1�����ǡ�a++ 1�������﷨����
//	printf("a+ +1 = %d\n", a + +1);//��ȷ��ʶ��Ϊ��a+ +1��
//	//printf("a++1 = %d\n", a++b);//���󣬲�ʶ��Ϊ��a+ +b�����ǡ�a++ b�������﷨����
//	printf("a+ +b = %d\n", a + +b);//��ȷ��ʶ��Ϊ��a+ +b��
//
//	system("pause");
//	return 0;
//}