#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Define maximum sizes
#define MAX_PROPERTIES 100

// Structure for property
typedef struct
{
    string name;
    string location;
    int total_spaces;
    int booked_spaces;
} Property;

// Global array to store properties
Property properties[MAX_PROPERTIES];
int property_count = 0;

// Function prototypes
void owner_menu(void);
void add_property(void);
void view_properties(void);
void remove_property(void);
void track_bookings(void);

void customer_menu(void);
void view_available_properties(void);
void book_space(void);

int main(void)
{
    int choice;
    do
    {
        printf("\n--- Booking Platform ---\n");
        printf("1. Property Owner Menu\n");
        printf("2. Customer Menu\n");
        printf("3. Exit\n");
        choice = get_int("Enter your choice: ");

        switch (choice)
        {
            case 1:
                owner_menu();
                break;
            case 2:
                customer_menu();
                break;
            case 3:
                printf("Exiting the platform. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 3);

    return 0;
}

// Owner menu
void owner_menu(void)
{
    int choice;
    do
    {
        printf("\n--- Property Owner Menu ---\n");
        printf("1. Add Property\n");
        printf("2. View Properties\n");
        printf("3. Remove Property\n");
        printf("4. Track Bookings\n");
        printf("5. Back to Main Menu\n");
        choice = get_int("Enter your choice: ");

        switch (choice)
        {
            case 1:
                add_property();
                break;
            case 2:
                view_properties();
                break;
            case 3:
                remove_property();
                break;
            case 4:
                track_bookings();
                break;
            case 5:
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);
}

// Add property
void add_property(void)
{
    if (property_count >= MAX_PROPERTIES)
    {
        printf("Property limit reached. Cannot add more properties.\n");
        return;
    }

    string name = get_string("Enter property name: ");
    string location = get_string("Enter property location: ");
    int total_spaces = get_int("Enter total space available: ");

    properties[property_count].name = name;
    properties[property_count].location = location;
    properties[property_count].total_spaces = total_spaces;
    properties[property_count].booked_spaces = 0;

    property_count++;
    printf("Property added successfully!\n");
}

// View properties
void view_properties(void)
{
    if (property_count == 0)
    {
        printf("No properties listed.\n");
        return;
    }

    printf("\n--- Listed Properties ---\n");
    for (int i = 0; i < property_count; i++)
    {
        printf("%d. %s (%s) - Spaces: %d, Booked: %d\n", i + 1, properties[i].name, properties[i].location,
               properties[i].total_spaces, properties[i].booked_spaces);
    }
}

// Remove property
void remove_property(void)
{
    view_properties();

    if (property_count == 0)
    {
        return;
    }

    int index = get_int("Enter property number to remove: ") - 1;

    if (index < 0 || index >= property_count)
    {
        printf("Invalid property number.\n");
        return;
    }

    for (int i = index; i < property_count - 1; i++)
    {
        properties[i] = properties[i + 1];
    }

    property_count--;
    printf("Property removed successfully!\n");
}

// Track bookings
void track_bookings(void)
{
    view_properties();
}

// Customer menu
void customer_menu(void)
{
    int choice;
    do
    {
        printf("\n--- Customer Menu ---\n");
        printf("1. View Available Properties\n");
        printf("2. Book Space\n");
        printf("3. Back to Main Menu\n");
        choice = get_int("Enter your choice: ");

        switch (choice)
        {
            case 1:
                view_available_properties();
                break;
            case 2:
                book_space();
                break;
            case 3:
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);
}

// View available properties
void view_available_properties(void)
{
    int found = 0;

    printf("\n--- Available Properties ---\n");
    for (int i = 0; i < property_count; i++)
    {
        if (properties[i].booked_spaces < properties[i].total_spaces)
        {
            found = 1;
            printf("%d. %s (%s) - Spaces Available: %d\n", i + 1, properties[i].name, properties[i].location,
                   properties[i].total_spaces - properties[i].booked_spaces);
        }
    }

    if (!found)
    {
        printf("No properties available for booking.\n");
    }
}

// Book space
void book_space(void)
{
    view_available_properties();
    if (property_count == 0)
    {
        return;
    }

    int index = get_int("Enter property number to book: ") - 1;
    if (index < 0 || index >= property_count)
    {
        printf("Invalid property number.\n");
        return;
    }

    if (properties[index].booked_spaces >= properties[index].total_spaces)
    {
        printf("No spaces available for this property.\n");
        return;
    }

    properties[index].booked_spaces++;
    printf("Space booked successfully for %s!\n", properties[index].name);
}
