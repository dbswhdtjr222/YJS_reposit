#include "receipter.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

#define ITEM_NUM (10)
#define ITEM_LENGTH (25)
#define MAX_MESSAGE_LEN (75)   
#define _CRT_SECURE_NO_WARNINGS#
/*receipt count*/
static int s_receipt_count = 1;

/* item, price */
static char s_item_name[ITEM_NUM][ITEM_LENGTH + 1];
static int s_item_pos = 0;
static double s_item_price[ITEM_LENGTH] = { 0, };

/* TIP */
static double s_tip = 0;

/* message buffer */
static char s_message[MAX_MESSAGE_LEN + 1] = { 0, };

int add_item(const char* name, double price)
{
	if (s_item_pos >= ITEM_NUM) {
		return FALSE;
	} else {
		strncpy(s_item_name[s_item_pos], name, ITEM_LENGTH+1);
		s_item_name[s_item_pos][ITEM_LENGTH] = '\0';
		s_item_price[s_item_pos] = price;
		++s_item_pos;

		return TRUE;
	}
}

void set_tip(double tip)
{
	s_tip = tip;
}

void set_message(const char* message)
{
	strncpy(s_message, message, MAX_MESSAGE_LEN+1);
	s_message[MAX_MESSAGE_LEN] = '\0';
}

int print_receipt(const char* filename, time_t timestamp)
{
	if (s_receipt_count >= 99999) {
		return FALSE;
	}
	double subtotal = 0;
	double tax = 0.0;
	double total = 0.0;
	char message_buffer[MAX_MESSAGE_LEN + 1];
	int i;
	FILE* fp;
	struct tm tm = *localtime(&timestamp);

	fp = fopen(filename, "w");
	if (fp == NULL) {
		perror("file opening Error");
		goto EndofFile;
	}
	/*head*/
	fputs("Charles' Seafood\n", fp);
	fputs("--------------------------------------------------\n", fp);

	/*date, year..*/
	fprintf(fp, "%d-%02d-%02d.%02d:%02d:%02d", tm.tm_year, tm.tm_mon, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
	fprintf(fp, "                          %05d\n", s_receipt_count);
	s_receipt_count++;
	fputs("--------------------------------------------------\n", fp);

	/* item */
	for (i = 0; i < s_item_pos; ++i) {
		fprintf(fp, "                 %s            %.2f\n", s_item_name[i], s_item_price[i]);
		subtotal += s_item_price[i];
	}
	fputs("\n", fp);
	/*subtotal, tax, tip*/
	tax = subtotal * 0.05;
	fprintf(fp, "                         Subtotal            %.2f\n", subtotal);
	fprintf(fp, "                              Tax             %.2f\n", tax);
	if (s_tip > 0) {
		fprintf(fp, "                              Tip             %.2f\n", s_tip);
	}
	total = subtotal + tax + s_tip;
	fprintf(fp, "                            Total            %.2f\n", total);
	fputs("\n", fp);
	/*message*/
	if (s_message[0] != '\0') {
		strncpy(message_buffer, s_message, MAX_MESSAGE_LEN + 1);
		message_buffer[MAX_MESSAGE_LEN] = '\0';
		fprintf(fp, "%s\n", message_buffer);
	}
	fputs("==================================================\n", fp);
	fputs("                                        Tax#-51234", fp);

EndofFile:
	s_item_pos = 0;
	s_tip = 0.0;
	s_message[0] = '\0';
	fclose(fp);
	
	return TRUE;
}