#!/bin/bash
DB_FILE="student_database.txt"
show_menu() {
    echo "Select an operation:"
    echo "a) Insert a record"
    echo "b) Delete a record"
    echo "c) Update a record"
    echo "d) Search for a record"
    echo "e) Exit"
    read -p "Enter your choice: " choice
}
insert_record() {
    read -p "Enter Student ID: " id
    read -p "Enter Student Name: " name
    read -p "Enter Student Grade: " grade
    echo "$id,$name,$grade" >> "$DB_FILE"
    echo "Record inserted successfully."
}
delete_record() {
    read -p "Enter Student ID to delete: " id
    if grep -q "^$id," "$DB_FILE"; then
        grep -v "^$id," "$DB_FILE" > temp_file && mv temp_file "$DB_FILE"
        echo "Record with ID $id deleted successfully."
    else
        echo "Record with ID $id not found."
    fi
}
update_record() {
    read -p "Enter Student ID to update: " id
    if grep -q "^$id," "$DB_FILE"; then
        read -p "Enter new Student Name: " name
        read -p "Enter new Student Grade: " grade
        grep -v "^$id," "$DB_FILE" > temp_file
        echo "$id,$name,$grade" >> temp_file
        mv temp_file "$DB_FILE"
        echo "Record with ID $id updated successfully."
    else
        echo "Record with ID $id not found."
    fi
}
search_record() {
    read -p "Enter Student ID to search: " id
    if grep -q "^$id," "$DB_FILE"; then
        echo "Record found:"
        grep "^$id," "$DB_FILE"
    else
        echo "Record with ID $id not found."
    fi
}
while true; do
    show_menu
    case $choice in
        a|A) insert_record ;;
        b|B) delete_record ;;
        c|C) update_record ;;
        d|D) search_record ;;
        e|E) echo "Exiting..."; exit 0 ;;
        *) echo "Invalid option. Please try again." ;;
    esac
done