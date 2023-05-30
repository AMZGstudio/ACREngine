def main():
    path = input("Enter location of the image: ")
    with open(path) as file:
        lines = file.readlines()

    width = len(lines[0]) - 1
    height = len(lines)

    print(lines)
    print(width, height)

    new_file = path.split('.')[0]+'.acge'
    with open(new_file, 'w') as image:
        image.write('acgev2.0;' + str(width) + ';' + str(height)+'\n')

        letters_and_value = {}
        for line in lines:
            for letter in line:
                if letter != '\n':
                    if letter not in letters_and_value.keys():
                        value = input("What is the color for " + letter + ": ")
                        letters_and_value[letter] = value
                    
                    image.write(letters_and_value[letter] + ';' + '#') 
            image.write('\n')

if __name__ == '__main__':
    main()