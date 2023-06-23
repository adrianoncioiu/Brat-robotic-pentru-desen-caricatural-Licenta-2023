input_file = "results.txt"
output_file = "initial.txt"
num_elements_per_line = 120

with open(input_file, "r") as file_in, open(output_file, "w") as file_out:
    elements = file_in.read().split()

    for i, element in enumerate(elements):
        file_out.write(element + " ")
        if (i + 1) % num_elements_per_line == 0:
            file_out.write("\n")
