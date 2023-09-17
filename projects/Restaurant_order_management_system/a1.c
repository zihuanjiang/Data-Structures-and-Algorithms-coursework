#include "a1.h"

Restaurant* initialize_restaurant(char* name){
	// free new_node and name	// why plus one here?
	Restaurant* new_node_Restaurant = malloc(sizeof(Restaurant));
	new_node_Restaurant->name = malloc(sizeof(char)*(strlen(name)+1));
    strcpy(new_node_Restaurant->name,name);

	Menu* menu = load_menu(MENU_FNAME);
    new_node_Restaurant->menu = menu;

    int num_completed_orders = 0;
    int num_pending_orders = 0;

	new_node_Restaurant->num_completed_orders = num_completed_orders;
	new_node_Restaurant->num_pending_orders = num_pending_orders;

	Queue* pending_orders = malloc(sizeof(Queue));
    QueueNode* head = NULL;
    QueueNode* tail = NULL;
    pending_orders->head = head;
    pending_orders->tail = tail;
    new_node_Restaurant->pending_orders = pending_orders;
	return new_node_Restaurant;
}


// helper functions to Menu* load_menu(char* fname)
char* copy_item_code(char* tem_item_code){
    char* new_item_code = malloc(sizeof(char)* ITEM_CODE_LENGTH);
    strcpy(new_item_code,tem_item_code);
    for (int i=0;i<ITEM_CODE_LENGTH;i++){
        tem_item_code[i] = '\0';
    }
    return new_item_code;
}
char* copy_item_name(char* tem_item_name){
    char* new_item_name = malloc(sizeof(char)* MAX_ITEM_NAME_LENGTH);
    strcpy(new_item_name,tem_item_name);
    for (int i=0;i<MAX_ITEM_NAME_LENGTH;i++){
        tem_item_name[i] = '\0';
    }
    return new_item_name;
}
double copy_item_cost(char* tem_item_cost){
    double new_item_cost;
    new_item_cost = atof(tem_item_cost);
    for (int i=0;i<10;i++){
        tem_item_cost[i] = '\0';
    }
    return new_item_cost;
}


Menu* load_menu(char* fname){
	Menu* new_node_Menu = malloc(sizeof(Menu));

    // initialize the value of structure
    int num_items = 0;
    char** item_codes = malloc(sizeof(char*)* 1);
    char** item_names = malloc(sizeof(char*)* 1);
    double* item_cost_per_unit = malloc(sizeof(double)* 1);

    // read and initialize temporary value
    FILE* file;
    file = fopen(fname, "r");
    int c = fgetc(file);
    int count_for_item_code = 0;
    int count_for_item_name = 0;
    int switch_to_item_cost = 0;
    int count_for_item_cost = 0;
    char* tem_item_code = malloc(sizeof(char)*ITEM_CODE_LENGTH);
    char* tem_item_name = malloc(sizeof(char)*MAX_ITEM_NAME_LENGTH);
    char* tem_item_cost = malloc(sizeof(char)*10);     // large enough
    char* comparing_entry = malloc(sizeof(char));
    int end_with_new_line_character_index = 1;
    int index_before_is_new_line_character = 1;

    while (c != EOF){    
        end_with_new_line_character_index = 1;
        comparing_entry[0] = c;

        if (count_for_item_code < ITEM_CODE_LENGTH - 1){
            tem_item_code[count_for_item_code] = c;
            count_for_item_code += 1;
            index_before_is_new_line_character = 1;
        }
        else if (count_for_item_code == ITEM_CODE_LENGTH - 1){
            tem_item_code[count_for_item_code] = '\0';
            count_for_item_code += 1;
            item_codes[num_items] = copy_item_code(tem_item_code);  
            index_before_is_new_line_character = 1;
        }
        else if (count_for_item_code > ITEM_CODE_LENGTH - 1 && switch_to_item_cost == 0){
            if (strcmp(comparing_entry,MENU_DELIM) != 0){
                tem_item_name[count_for_item_name] = c;
                count_for_item_name += 1;
                index_before_is_new_line_character = 1;
            }
            else{
                tem_item_name[count_for_item_name] = '\0';
                switch_to_item_cost = 1;
                item_names[num_items] = copy_item_name(tem_item_name);
                index_before_is_new_line_character = 1;
            }
        }
        else if (switch_to_item_cost == 1){
            if (c != '\n' && c != '$'){
                tem_item_cost[count_for_item_cost] = c;
                count_for_item_cost += 1;
                index_before_is_new_line_character = 1;
            }
            else if (c == '\n') {
                if (index_before_is_new_line_character == 1){
                    end_with_new_line_character_index = 0;
                    item_cost_per_unit[num_items] = copy_item_cost(tem_item_cost);
                    num_items += 1;
                    count_for_item_code = 0;
                    count_for_item_name = 0;
                    switch_to_item_cost = 0;
                    count_for_item_cost = 0;
                    item_codes = realloc(item_codes, sizeof(char*)* (num_items+1));
                    item_names = realloc(item_names, sizeof(char*)* (num_items+1));
                    item_cost_per_unit = realloc(item_cost_per_unit, sizeof(double)* (num_items+1));
                }
            }
        }
        if (c == '\n'){
            index_before_is_new_line_character = 0;
        }
        c = fgetc(file);
    }
    if (end_with_new_line_character_index == 1 && index_before_is_new_line_character == 1){
    // these two lines are base on the assumption that there is no \n at the end of the file
    item_cost_per_unit[num_items] = copy_item_cost(tem_item_cost);
    num_items += 1;
    }
    else if (end_with_new_line_character_index == 0){
        item_codes = realloc(item_codes, sizeof(char*)* (num_items));
        item_names = realloc(item_names, sizeof(char*)* (num_items));
        item_cost_per_unit = realloc(item_cost_per_unit, sizeof(double)* (num_items));
    }


    fclose(file);
    // connect the value to the structure
    new_node_Menu->num_items = num_items;
    new_node_Menu->item_codes = item_codes;
    new_node_Menu->item_names = item_names;
    new_node_Menu->item_cost_per_unit = item_cost_per_unit;

    free(tem_item_code);
    free(tem_item_cost);
    free(tem_item_name);
    free(comparing_entry);
	return new_node_Menu;
}



Order* build_order(char* items, char* quantities){
    Order* new_node_order = malloc(sizeof(Order));
    int num_items;
    int string_length_items = strlen(items);
    num_items = string_length_items / (ITEM_CODE_LENGTH - 1);

    // initialize node values
    char** item_codes = malloc(sizeof(char*)*num_items);
    int* item_quantities = malloc(sizeof(int)*num_items);

    // initialize temporary value and helping index
    char* tem_item_code = malloc(sizeof(char)*ITEM_CODE_LENGTH);
    char* tem_item_quantities = malloc(sizeof(char)*10);
    char* comparing_entry = malloc(sizeof(char)*strlen(MENU_DELIM));
    int string_length_quantities = strlen(quantities);
    int index_of_tem_item_quantities = 0;
    int index_of_num_item = 0;


    for(int i=0; i < num_items ; i++){
        strncpy(tem_item_code,items + (ITEM_CODE_LENGTH-1) * i , ITEM_CODE_LENGTH-1);
        tem_item_code[ITEM_CODE_LENGTH-1] = '\0';
        item_codes[i] = copy_item_code(tem_item_code);
    }

    for(int k=0; k < string_length_quantities ; k++){
        strncpy(comparing_entry, quantities + k, strlen(MENU_DELIM));
        if (strcmp(comparing_entry, MENU_DELIM) != 0){
            index_of_tem_item_quantities++;
        }
        else if (strcmp(comparing_entry, MENU_DELIM) == 0){
            strncpy(tem_item_quantities, quantities + k - index_of_tem_item_quantities , index_of_tem_item_quantities);
            index_of_tem_item_quantities++;
            tem_item_quantities[index_of_tem_item_quantities] = '\0';
            index_of_tem_item_quantities = 0;
            item_quantities[index_of_num_item] = copy_item_cost(tem_item_quantities);
            index_of_num_item++;
        }

        if (k == string_length_quantities -1 && (strcmp(comparing_entry, MENU_DELIM) != 0)){
            strncpy(tem_item_quantities, quantities + k - index_of_tem_item_quantities +1, index_of_tem_item_quantities);
            tem_item_quantities[index_of_tem_item_quantities] = '\0';
            item_quantities[index_of_num_item] = copy_item_cost(tem_item_quantities);
        } 
    }

    // connect the value to the structure
    new_node_order->num_items = num_items;
    new_node_order->item_codes = item_codes;
    new_node_order->item_quantities = item_quantities;

    free(tem_item_code);
    free(tem_item_quantities);
    free(comparing_entry);
    return new_node_order;
}




void enqueue_order(Order* order, Restaurant* restaurant){
    QueueNode* new_head = malloc(sizeof(QueueNode));
    new_head->order = order;
    new_head->next = restaurant->pending_orders->head;

    if (restaurant->pending_orders->tail == NULL){
        restaurant->pending_orders->tail = new_head;
    }
    restaurant->pending_orders->head = new_head;
    restaurant->num_pending_orders++;
}



Order* dequeue_order(Restaurant* restaurant){
    QueueNode* finding_tail = malloc(sizeof(QueueNode));
    Order* result_dequeued_order = malloc(sizeof(Order));
    finding_tail = restaurant->pending_orders->head;
    result_dequeued_order = restaurant->pending_orders->tail->order;
    // only one order in queue
    if (restaurant->pending_orders->head == restaurant->pending_orders->tail){
        restaurant->pending_orders->head = NULL;
        restaurant->pending_orders->tail = NULL;
    }
    // start finding the tail
    while (finding_tail->next != restaurant->pending_orders->tail){
        finding_tail = finding_tail->next;
    }
    // now finding_tail->next = restaurant->pending_orders->tail
    finding_tail->next = NULL;
    restaurant->pending_orders->tail = finding_tail;
    finding_tail = NULL;

    restaurant->num_completed_orders++;
    restaurant->num_pending_orders--;
    return result_dequeued_order;
}





double get_item_cost(char* item_code, Menu* menu){
    for (int i = 0; i < menu->num_items; i++){
        if (strcmp(item_code,menu->item_codes[i]) == 0){
            return menu->item_cost_per_unit[i];
        }
    }
    return menu->item_cost_per_unit[0]; // not proved, need consideration
}

double get_order_subtotal(Order* order, Menu* menu){
    double subtotal = 0;
    double tem_price = 0;
    char* tem_item_code = malloc(sizeof(char) * ITEM_CODE_LENGTH);
    for (int i = 0; i < order->num_items; i++){
        tem_item_code = order->item_codes[i];
        tem_price = get_item_cost(tem_item_code,menu);
        subtotal += tem_price;
    }
    free(tem_item_code);
    return subtotal;
}

double get_order_total(Order* order, Menu* menu){
    double subtotal = get_order_subtotal(order,menu);
    double total = subtotal * (100+TAX_RATE);
    total = total / (double) 100.00;
    return total;
}

int get_num_completed_orders(Restaurant* restaurant){
    return restaurant->num_completed_orders;
}
int get_num_pending_orders(Restaurant* restaurant){
    return restaurant->num_pending_orders;
}

void clear_order(Order** order){
    Order* pointer_to_struct_order = *order;
    free(pointer_to_struct_order->item_quantities);
    for (int i = 0; i < pointer_to_struct_order->num_items; i++){
        free(pointer_to_struct_order->item_codes[i]);
    }
    free(pointer_to_struct_order->item_codes);
    free(pointer_to_struct_order);
    pointer_to_struct_order = NULL;
}

void clear_menu(Menu** menu){
    Menu* pointer_to_struct_menu = *menu;
    free(pointer_to_struct_menu->item_cost_per_unit);
    for (int i = 0; i < pointer_to_struct_menu->num_items; i++){
        free(pointer_to_struct_menu->item_codes[i]);
        free(pointer_to_struct_menu->item_names[i]);
    }
    free(pointer_to_struct_menu->item_codes);
    free(pointer_to_struct_menu->item_names);
    free(pointer_to_struct_menu);
    pointer_to_struct_menu = NULL;
}

void close_restaurant(Restaurant** restaurant){

	clear_menu(&((*restaurant)->menu));

	QueueNode *temp = ((*restaurant)->pending_orders)->head;
	while ( temp != NULL){
		clear_order(&(temp->order));
		temp = temp->next;
	}
	if (((*restaurant)->pending_orders)->head != ((*restaurant)->pending_orders)->tail) free(((*restaurant)->pending_orders)->head);
	free(((*restaurant)->pending_orders)->tail);
	free((*restaurant)->pending_orders);
	
	free((*restaurant)->name);
	free(*restaurant);
	*restaurant = NULL;
}





void print_menu(Menu* menu){
	fprintf(stdout, "--- Menu ---\n");
	for (int i = 0; i < menu->num_items; i++){
		fprintf(stdout, "(%s) %s: %.2f\n", 
			menu->item_codes[i], 
			menu->item_names[i], 
			menu->item_cost_per_unit[i]	
		);
	}
}


void print_order(Order* order){
	for (int i = 0; i < order->num_items; i++){
		fprintf(
			stdout, 
			"%d x (%s)\n", 
			order->item_quantities[i], 
			order->item_codes[i]
		);
	}
}


void print_receipt(Order* order, Menu* menu){
	for (int i = 0; i < order->num_items; i++){
		double item_cost = get_item_cost(order->item_codes[i], menu);
		fprintf(
			stdout, 
			"%d x (%s)\n @$%.2f ea \t %.2f\n", 
			order->item_quantities[i],
			order->item_codes[i], 
			item_cost,
			item_cost * order->item_quantities[i]
		);
	}
	double order_subtotal = get_order_subtotal(order, menu);
	double order_total = get_order_total(order, menu);
	
	fprintf(stdout, "Subtotal: \t %.2f\n", order_subtotal);
	fprintf(stdout, "               -------\n");
	fprintf(stdout, "Tax %d%%: \t$%.2f\n", TAX_RATE, order_total);
	fprintf(stdout, "              ========\n");
}