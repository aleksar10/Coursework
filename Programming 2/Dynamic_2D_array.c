#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int toBend_int(int lend_value)
{
    return ((lend_value & 0xFF000000) >> 24) |
           ((lend_value & 0x00FF0000) >> 8)  |
           ((lend_value & 0x0000FF00) << 8)  |
           ((lend_value & 0x000000FF) << 24);
}

unsigned short toBend_us(unsigned short lend_value)
{
    return ((lend_value & 0xFF00) >> 8) | ((lend_value & 0x00FF) << 8);
}

void add_row(int ***rows_ptr_table, unsigned short **row_size_table, unsigned short *rows_count,
             unsigned short columns, unsigned short row_idx, FILE *file_obj)
{
    int *row_ptr, value, i;

    row_ptr = (int*)malloc(columns * sizeof(int));
    for (i = 0; i < columns; i++)
    {
        if (file_obj == NULL)
            scanf("%i", &value);
        else
        {
            fread(&value, sizeof(int), 1, file_obj);
            value = toBend_int(value);
        }
        *(row_ptr + i) = value;
    }

    *rows_ptr_table = (int**)realloc(*rows_ptr_table, (*rows_count + 1) * sizeof(int**));
    *row_size_table = (unsigned short*)realloc(*row_size_table, (*rows_count + 1) * sizeof(unsigned short*));

    for (i = *rows_count; i > row_idx; i--)
    {
        *(*rows_ptr_table + i) = *(*rows_ptr_table + i - 1);
        *(*row_size_table + i) = *(*row_size_table + i - 1);
    }

    *(*rows_ptr_table + row_idx) = row_ptr;
    *(*row_size_table + row_idx) = columns;
    (*rows_count)++;
}

void remove_row(int ***rows_ptr_table, unsigned short **row_size_table,
                unsigned short *rows_count, unsigned short row_index)
{
    int i;

    if (row_index >= *rows_count)
        return;

    if (*rows_count > 1)
    {
        (*rows_count)--;
        free(*(*rows_ptr_table + row_index));
        for (i = row_index; i < *(rows_count); i++)
        {
            *(*rows_ptr_table + i) = *(*rows_ptr_table + i + 1);
            *(*row_size_table + i) = *(*row_size_table + i + 1);
        }
        *rows_ptr_table = (int **)realloc(*rows_ptr_table, (*rows_count) * sizeof(int**));
        *row_size_table = (unsigned short *)realloc(*row_size_table, (*rows_count) * sizeof(unsigned short*));
    }
    else if (*rows_count == 1)
    {
        (*rows_count)--;
        free(**rows_ptr_table);
        free(*row_size_table);
        free(*rows_ptr_table);
        *row_size_table = NULL;
        *rows_ptr_table = NULL;
    }
}

void add_column_to_row(int **rows_ptr_table, unsigned short *row_size_table,
                       unsigned short row_index, unsigned short col_index, int value)
{
    unsigned short i;

    if (col_index > *(row_size_table + row_index))
        col_index = *(row_size_table + row_index);

    *(rows_ptr_table + row_index) = (int*)realloc(*(rows_ptr_table + row_index), (*(row_size_table + row_index) + 1) * sizeof(int));

    for (i = *(row_size_table + row_index); i > col_index; i--)
    {
        *(*(rows_ptr_table + row_index) + i) = *(*(rows_ptr_table + row_index) + i - 1);
    }
    *(*(rows_ptr_table + row_index) + col_index) = value;
    (*(row_size_table + row_index))++;
}

void remove_column(int ***rows_ptr_table, unsigned short **row_size_table,
                unsigned short *rows_count, int col_index)
{
    int i, j;

    if (*rows_count == 0)
        return;

    for (i = *rows_count - 1; i >= 0; i--)
    {
        if (col_index >= *(*row_size_table + i))
            continue;
        (*(*row_size_table + i))--;
        if (*(*row_size_table + i) == 0)
            remove_row(rows_ptr_table, row_size_table, rows_count, i);
        else
        {
            if (col_index > -1)
            {
                for (j = col_index; j < *(*row_size_table + i); j++)
                {
                    *(*(*rows_ptr_table + i) + j) = *(*(*rows_ptr_table + i) + j + 1);
                }
            }
            *(*rows_ptr_table + i) = (int*)realloc(*(*rows_ptr_table + i), (*(*row_size_table + i)) * sizeof(int));
        }
    }
}

void remove_column_from_row(int ***rows_ptr_table, unsigned short **row_size_table,
                            unsigned short *rows_count, unsigned short row_index, unsigned short col_index)
{
    int i;

    if (*rows_count == 0)
        return;

    if ((row_index > (*rows_count - 1)) ||
        (col_index >= *(*row_size_table + row_index)))
        return;
    (*(*row_size_table + row_index))--;
    if (*(*row_size_table + row_index) == 0)
        remove_row(rows_ptr_table, row_size_table, rows_count, row_index);
    else
    {
        for (i = col_index; i < *(*row_size_table + row_index); i++)
        {
            *(*(*rows_ptr_table + row_index) + i) = *(*(*rows_ptr_table + row_index) + i + 1);
        }
        *(*rows_ptr_table + row_index) = (int*)realloc(*(*rows_ptr_table + row_index),
                                                      (*(*row_size_table + row_index)) * sizeof(int));
    }
}

void handle_AFR(int ***rows_ptr_table, unsigned short **row_size_table,
                unsigned short *rows_count)
{
    int w;

    scanf("%i", &w);
    add_row(rows_ptr_table, row_size_table, rows_count, w, 0, NULL);
}

void handle_ALR(int ***rows_ptr_table, unsigned short **row_size_table,
                unsigned short *rows_count)
{
    int w;

    scanf("%i", &w);
    add_row(rows_ptr_table, row_size_table, rows_count, w, *rows_count, NULL);
}

void handle_AFC(int ***rows_ptr_table, unsigned short **row_size_table,
                unsigned short *rows_count)
{
    int h, i, value;

    scanf("%i", &h);
    for (i = 0; i < h; i++)
    {
        if (i < *rows_count)
        {
            scanf("%i", &value);
            add_column_to_row(*rows_ptr_table, *row_size_table, i, 0, value);
        }
        else
            add_row(rows_ptr_table, row_size_table, rows_count, 1, *rows_count, NULL);
    }
}

void handle_ALC(int ***rows_ptr_table, unsigned short **row_size_table,
                unsigned short *rows_count)
{
    int h, i, value;

    scanf("%i", &h);
    for (i = 0; i < h; i++)
    {
        if (i < *rows_count)
        {
            scanf("%i", &value);
            add_column_to_row(*rows_ptr_table, *row_size_table, i, *(*row_size_table + i), value);
        }
        else
            add_row(rows_ptr_table, row_size_table, rows_count, 1, *rows_count, NULL);
    }
}

void handle_IBR(int ***rows_ptr_table, unsigned short **row_size_table,
                unsigned short *rows_count)
{
    int r, w;

    scanf("%i%i", &r, &w);
    if (r < *rows_count)
        add_row(rows_ptr_table, row_size_table, rows_count, w, r, NULL);
}

void handle_IAR(int ***rows_ptr_table, unsigned short **row_size_table,
                unsigned short *rows_count)
{
    int r, w;

    scanf("%i%i", &r, &w);
    if (r < *rows_count)
        add_row(rows_ptr_table, row_size_table, rows_count, w, r + 1, NULL);
}

void handle_IBC(int ***rows_ptr_table, unsigned short **row_size_table,
                unsigned short *rows_count)
{
    int c, h, i, value;

    scanf("%i%i", &c, &h);
    for (i = 0; i < h; i++)
    {
        if (i < *rows_count)
        {
            scanf("%i", &value);
            add_column_to_row(*rows_ptr_table, *row_size_table, i, c, value);
        }
        else
            add_row(rows_ptr_table, row_size_table, rows_count, 1, *rows_count, NULL);
    }
}

void handle_IAC(int ***rows_ptr_table, unsigned short **row_size_table,
                unsigned short *rows_count)
{
    int c, h, i, value;

    scanf("%i%i", &c, &h);
    for (i = 0; i < h; i++)
    {
        if (i < *rows_count)
        {
            scanf("%i", &value);
            add_column_to_row(*rows_ptr_table, *row_size_table, i, c + 1, value);
        }
        else
            add_row(rows_ptr_table, row_size_table, rows_count, 1, *rows_count, NULL);
    }
}

void handle_SWR(int **rows_ptr_table, unsigned short *row_size_table,
                unsigned short rows_count)
{
    int r, s, tmp_row_size, *tmp_row_ptr;

    scanf("%i%i", &r, &s);
    if ((r < rows_count) && (s < rows_count))
    {
        tmp_row_ptr = *(rows_ptr_table + r);
        *(rows_ptr_table + r) = *(rows_ptr_table + s);
        *(rows_ptr_table + s) = tmp_row_ptr;
        tmp_row_size = *(row_size_table + r);
        *(row_size_table + r) = *(row_size_table + s);
        *(row_size_table + s) = tmp_row_size;
    }
}

void handle_SWC(int **rows_ptr_table, unsigned short *row_size_table,
                unsigned short rows_count)
{
    int c, d, i, tmp_value;

    scanf("%i%i", &c, &d);
    for (i = 0; i < rows_count; i++)
    {
        if ((c < *(row_size_table + i)) && (d < *(row_size_table + i)))
        {
            tmp_value = *((*(rows_ptr_table + i)) + c);
            *((*(rows_ptr_table + i)) + c) = *((*(rows_ptr_table + i)) + d);
            *((*(rows_ptr_table + i)) + d) = tmp_value;
        }
    }
}

void handle_DFR(int ***rows_ptr_table, unsigned short **row_size_table,
                unsigned short *rows_count)
{
    remove_row(rows_ptr_table, row_size_table, rows_count, 0);
}

void handle_DLR(int ***rows_ptr_table, unsigned short **row_size_table,
                unsigned short *rows_count)
{
    remove_row(rows_ptr_table, row_size_table, rows_count, *rows_count - 1);
}

void handle_DFC(int ***rows_ptr_table, unsigned short **row_size_table,
                unsigned short *rows_count)
{
    remove_column(rows_ptr_table, row_size_table, rows_count, 0);
}

void handle_DLC(int ***rows_ptr_table, unsigned short **row_size_table,
                unsigned short *rows_count)
{
    remove_column(rows_ptr_table, row_size_table, rows_count, -1);
}

void handle_RMR(int ***rows_ptr_table, unsigned short **row_size_table,
                unsigned short *rows_count)
{
    int r;

    scanf("%i", &r);
    remove_row(rows_ptr_table, row_size_table, rows_count, r);
}

void handle_RMC(int ***rows_ptr_table, unsigned short **row_size_table,
                unsigned short *rows_count)
{
    int c;

    scanf("%i", &c);
    remove_column(rows_ptr_table, row_size_table, rows_count, c);
}

void handle_RMB(int ***rows_ptr_table, unsigned short **row_size_table,
                unsigned short *rows_count)
{
    int r, h, c, w, i, j;

    scanf("%i%i%i%i", &r, &h, &c, &w);
    for (i = r + h - 1; i >= r; i--)
    {
        for (j = c + w - 1; j >= c; j--)
        {
            remove_column_from_row(rows_ptr_table, row_size_table, rows_count, i, j);
        }
    }
}

void handle_ISB(int ***rows_ptr_table, unsigned short **row_size_table,
                unsigned short *rows_count)
{
    int r, c, h, value, w, i, j;

    scanf("%i%i%i%i", &r, &c, &h, &w);
    for (i = r; i < (r + h); i++)
    {
        if (i < *rows_count)
        {
            for (j = c; j < (c + w); j++)
            {
                scanf("%i", &value);
                add_column_to_row(*rows_ptr_table, *row_size_table, i, j, value);
            }
        }
        else
            add_row(rows_ptr_table, row_size_table, rows_count, w, *rows_count, NULL);
    }
}

void handle_WRF(int **rows_ptr_table, unsigned short *row_size_table,
                int rows_count)
{
    FILE *file_obj;
    char *file_name;
    int col_number, col_number_lend, i, j;
    int value;
    char tmp = '\n';

    file_name = (char*)malloc(17 * sizeof(char));
    scanf("%s", file_name);
    file_obj = fopen(file_name, "wb");
    fprintf(file_obj, "%i%c", rows_count, tmp);
    for (i = 0; i < rows_count; i++)
    {
        col_number = *(row_size_table + i);
        col_number_lend = col_number;
        col_number = toBend_us(col_number);

        fwrite(&col_number, sizeof(unsigned short), 1, file_obj);

        for (j = 0; j < col_number_lend; j++)
        {
            value = *(*(rows_ptr_table + i) + j);
            value = toBend_int(value);
            fwrite(&value, sizeof(int), 1, file_obj);
        }
    }
    fclose(file_obj);
    free(file_name);
}

void handle_RDF(int ***rows_ptr_table, unsigned short **row_size_table,
                unsigned short *rows_count)
{
    FILE *file_obj;
    char *file_name;
    char tmp;
    int i, rows_number, col_number;

    rows_number = *rows_count;
    for (i = rows_number - 1; i >= 0; i--)
        remove_row(rows_ptr_table, row_size_table, rows_count, i);

    file_name = (char*)malloc(17 * sizeof(char));
    scanf("%s", file_name);
    file_obj = fopen(file_name, "rb");
    fscanf(file_obj, "%i%c", &rows_number, &tmp);
    for (i = 0; i < rows_number; i++)
    {
        fread(&col_number, sizeof(unsigned short), 1, file_obj);
        col_number = toBend_us((unsigned short)col_number);
        add_row(rows_ptr_table, row_size_table, rows_count, col_number, i, file_obj);
    }
    fclose(file_obj);
    free(file_name);
}

void handle_PRT(int **rows_ptr_table, unsigned short *row_size_table,
                unsigned short rows_count)
{
    unsigned short i, j;

    printf("%i\n", rows_count);
    for (i = 0; i < rows_count; i++)
    {
        printf("%i ", *(row_size_table + i));
        for (j = 0; j < *(row_size_table + i); j++)
        {
            printf("%i ", *(*(rows_ptr_table + i) + j));
        }
        printf("\n");
    }
}

int main(void)
{
    char *command;
    int **head = NULL;
    unsigned short num_rows = 0;
    unsigned short *num_col_ptr = NULL;
    unsigned short i;

    command = (char*)calloc(128, sizeof(char));
    while (scanf("%s", command) > 0)
    {
        if (strcmp(command, "AFR") == 0)
            handle_AFR(&head, &num_col_ptr, &num_rows);
        else if (strcmp(command, "ALR") == 0)
            handle_ALR(&head, &num_col_ptr, &num_rows);
        else if (strcmp(command, "AFC") == 0)
            handle_AFC(&head, &num_col_ptr, &num_rows);
        else if (strcmp(command, "ALC") == 0)
            handle_ALC(&head, &num_col_ptr, &num_rows);
        else if (strcmp(command, "IBR") == 0)
            handle_IBR(&head, &num_col_ptr, &num_rows);
        else if (strcmp(command, "IAR") == 0)
            handle_IAR(&head, &num_col_ptr, &num_rows);
        else if (strcmp(command, "IBC") == 0)
            handle_IBC(&head, &num_col_ptr, &num_rows);
        else if (strcmp(command, "IAC") == 0)
            handle_IAC(&head, &num_col_ptr, &num_rows);
        else if (strcmp(command, "SWR") == 0)
            handle_SWR(head, num_col_ptr, num_rows);
        else if (strcmp(command, "SWC") == 0)
            handle_SWC(head, num_col_ptr, num_rows);
        else if (strcmp(command, "DFR") == 0)
            handle_DFR(&head, &num_col_ptr, &num_rows);
        else if (strcmp(command, "DLR") == 0)
            handle_DLR(&head, &num_col_ptr, &num_rows);
        else if (strcmp(command, "DFC") == 0)
            handle_DFC(&head, &num_col_ptr, &num_rows);
        else if (strcmp(command, "DLC") == 0)
            handle_DLC(&head, &num_col_ptr, &num_rows);
        else if (strcmp(command, "RMR") == 0)
            handle_RMR(&head, &num_col_ptr, &num_rows);
        else if (strcmp(command, "RMC") == 0)
            handle_RMC(&head, &num_col_ptr, &num_rows);
        else if (strcmp(command, "RMB") == 0)
            handle_RMB(&head, &num_col_ptr, &num_rows);
        else if (strcmp(command, "ISB") == 0)
            handle_ISB(&head, &num_col_ptr, &num_rows);
        else if (strcmp(command, "WRF") == 0)
            handle_WRF(head, num_col_ptr, num_rows);
        else if (strcmp(command, "RDF") == 0)
            handle_RDF(&head, &num_col_ptr, &num_rows);
        else if (strcmp(command, "PRT") == 0)
            handle_PRT(head, num_col_ptr, num_rows);
        else if (strcmp(command, "END") == 0)
            break;
        else
            continue;
    }

    free(command);
    free(num_col_ptr);
    for (i = 0; i < num_rows; i++)
        free(*(head + i));
    free(head);

    return 0;
}
