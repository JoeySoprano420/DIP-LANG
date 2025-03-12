# Sample table: A structured diagram-table representation
table = [
    {"Symbol": "Health Informatics", "Hex": "0x322", "Binary": "1100011010"},
    {"Symbol": "Wearable Tech", "Hex": "0x323", "Binary": "invalid_binary"},
    {"Symbol": "IoT Wearables", "Hex": "0x324", "Binary": "1100011100"}
]

# Reference Set Assembly Function
def assemble_reference_set_with_dip(table):
    reference_set = {}
    deferred_errors = []  # For Deferred Error Handling
    memory_packets = []  # Memory Packetization for efficient storage

    for row in table:
        try:
            # Step 1: Diagram-Table Execution
            memory_packet = {
                "Symbol": row["Symbol"],
                "HexValue": int(row["Hex"], 16),  # Convert Hexadecimal
                "BinaryValue": int(row["Binary"], 2)  # Convert Binary
            }
            
            # Step 2: Add to Memory Packetization for Encapsulation
            memory_packets.append(memory_packet)
            reference_set[row["Symbol"]] = memory_packet  # Add to Reference Set

        except ValueError as e:
            # Step 3: Deferred Error Handling with Context
            deferred_errors.append({"Row": row, "Error": str(e)})

    # Contextual Error Handling
    if deferred_errors:
        print("\nDeferred Errors:")
        for error in deferred_errors:
            print(f"Context: {error['Row']}, Error: {error['Error']}")

    return reference_set, memory_packets

# Call the function to process the table
reference_set, memory_packets = assemble_reference_set_with_dip(table)

# Output Results
print("\nAssembled Reference Set:")
for symbol, data in reference_set.items():
    print(f"{symbol} -> Hex: {data['HexValue']}, Binary: {data['BinaryValue']}")

print("\nMemory Packets (for encapsulation):", memory_packets)
