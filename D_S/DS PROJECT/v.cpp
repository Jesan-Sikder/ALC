int useroptions;
    User* currentUser = NULL;
    printf("\n");
    printf("\t\t\t\t\t\t==================== Welcome to Majestic Suite ====================\n");

    while (1) {

        printf("\n");
        printf("\t\t\t\t\t\t==================== A Hotel Management System ====================\n\n");
        printf("\t\t\t\t\t\t1. Sign Up\n");
        printf("\t\t\t\t\t\t2. Sign In\n");
        printf("\t\t\t\t\t\t3. View Rooms (Non-AC, AC, VIP)\n");
        printf("\t\t\t\t\t\t4. Book a Room\n");
        printf("\t\t\t\t\t\t5. View Booking Details\n");
        printf("\t\t\t\t\t\t6. View VIP Facilities\n");
        printf("\t\t\t\t\t\t7. Add to Wishlist\n");
        printf("\t\t\t\t\t\t8. View Wishlist\n");
        printf("\t\t\t\t\t\t9. Cancel Booking\n");
        printf("\t\t\t\t\t\t10. Extend Stay\n");
        printf("\t\t\t\t\t\t11. Exit\n\n");
        printf("\t\t\t\t\t\t==================================================================\n");
        printf("\t\t\t\t\t\tSelect an useroptions: ");
        scanf("%d", &useroptions);

        if (useroptions == 1) {
            signUp(&userList);
        } else if (useroptions == 2) {
            currentUser = signIn(userList);
        } else if (useroptions == 3) {
            printf("\t\t\t\t\t\tView rooms by type:\n");
            printf("\t\t\t\t\t\t1. Non-AC\n");
            printf("\t\t\t\t\t\t2. AC\n");
            printf("\t\t\t\t\t\t3. VIP\n");
            printf("\t\t\t\t\t\tEnter room type: ");
            int roomType;
            scanf("%d", &roomType);
            displayRooms(rooms, roomType - 1); // 0: Non-AC, 1: AC, 2: VIP
        } else if (useroptions == 4) {
            if (currentUser == NULL) {
                printf("\t\t\t\t\t\tPlease sign in first.\n");
            } else {
                int room_number, age, customer_id, days_of_stay, num_guests, num_children, 
                 check_in_day, check_in_month, check_in_year,  check_out_day, check_out_month, check_out_year;
                char name[100], phone_number[12], NID[100],j[1];

                printf("\t\t\t\t\t\tEnter Room Number to Book: ");
                scanf("%d", &room_number);

                // Check room availability before asking for details
                if (checkRoomAvailability(rooms, room_number) == 0) {
                    printf("\t\t\t\t\t\tInvalid request: Room is not available or already booked.\n");
                } else {
                    // If room is available, proceed with asking for customer details
                    printf("\t\t\t\t\t\tEnter Customer ID: ");
                    scanf("%d", &customer_id);
                    printf("\t\t\t\t\t\tEnter Full Name: ");
                    scanf(" %[^\n]", name);
                    printf("\t\t\t\t\t\tEnter NID: ");
                    scanf(" %[^\n]", NID);
                    printf("\t\t\t\t\t\tEnter Age: ");
                    scanf("%d", &age);
                    printf("\t\t\t\t\t\tEnter Number of Guests: ");
                    scanf("%d", &num_guests);
                    printf("\t\t\t\t\t\tEnter Number of Children: ");
                    scanf("%d", &num_children);
                    printf("\t\t\t\t\t\tEnter Phone Number 11 digit only: ");
                    scanf("%s", phone_number);
                    printf("\t\t\t\t\t\tEnter Check-In Date (DD-MM-YYYY): ");
                    scanf("%d%c%d%c%d", &check_in_day,&j,&check_in_month,&j,&check_in_year);
                    printf("\t\t\t\t\t\tEnter Check-Out Date (DD-MM-YYYY): ");
                    scanf("%d%c%d%c%d", &check_out_day,&j,&check_out_month,&j,&check_out_year);

                    // Calculate the days of stay
                    days_of_stay = calculateStayDuration( check_in_day, check_in_month, check_in_year,  check_out_day, check_out_month, check_out_year);
                    Room* bookedRoom = bookRoom(rooms, room_number);
                    if (bookedRoom) {
                        int total_amount = bookedRoom->price * days_of_stay;
                       
                        addCustomer(&customerList, customer_id, name, age, room_number, total_amount, days_of_stay, num_guests, num_children, check_in_day, check_in_month, check_in_year,  check_out_day, check_out_month, check_out_year, phone_number);

                        printf("\t\t\t\t\t\tRoom booked successfully! Total amount: %d\n", total_amount);
                    } else {
                        printf("\t\t\t\t\t\tRoom is not available.\n");
                    }
                }
            }
        } else if (useroptions == 5) {
            viewBookingDetails(customerList);
        } else if (useroptions == 6) {
            displayVIPFacilities();
        } else if (useroptions == 7) {
            if (currentUser != NULL) {
                int room_number;
                printf("\t\t\t\t\t\tEnter room number to add to wishlist: ");
                scanf("%d", &room_number);
                addToWishlist(&wishlist, room_number);
                printf("\t\t\t\t\t\tRoom %d added to wishlist.\n", room_number);
            }
        } else if (useroptions == 8) {
            viewWishlist(wishlist);
        } else if (useroptions == 9) {
            if (currentUser != NULL) {
                int customer_id;
                printf("\t\t\t\t\t\tEnter Customer ID to cancel booking: ");
                scanf("%d", &customer_id);
                cancelBooking(&customerList, customer_id);
            }
        } else if (useroptions == 10) {
            if (currentUser != NULL) {
                int customer_id;
                printf("\t\t\t\t\t\tEnter Customer ID to extend stay: ");
                scanf("%d", &customer_id);
                extendStay(customerList, customer_id);
            }
        } else if (useroptions == 11) {
            printf("\t\t\t\t\t\tThank you for using the system.\n");
            exit(0);
        } else {
            printf("\t\t\t\t\t\tInvalid choice! Please try again.\n");
        }
    }