import random 

scores=list({})
for i in range(47):
    scores.append(list({}))

def first_number(text):
    digits = []
    for char in text:
        if char.isdigit():
            digits.append(char)
        elif digits:  # Stop when non-digit found after digits
            break
    if digits:
        return int(''.join(digits))
    return None
def all_numbers(text):
    numbers = []
    current_digits = []
    
    for char in text:
        if char.isdigit():
            current_digits.append(char)
        elif current_digits:
            # Convert collected digits to number and add to list
            numbers.append(int(''.join(current_digits)))
            current_digits = []
    
    # Add the last number if the string ends with digits
    if current_digits:
        numbers.append(int(''.join(current_digits)))
    
    return numbers

def next_test():
    last_numbers = [line[-1] for line in scores]
    
    unique_last_numbers = sorted(set(last_numbers))
    smallest = unique_last_numbers[0]
    second_smallest = unique_last_numbers[1] if len(unique_last_numbers) > 1 else smallest
    
    # Find all lines that have the smallest or second smallest last number
    candidate_lines = []
    for i, line in enumerate(scores):
        if line[-1] == smallest or line[-1] == second_smallest:
            candidate_lines.append(i)
    
    if not candidate_lines:
        return random.randint(0, len(scores) - 1)
    
    weights = []
    for line_idx in candidate_lines:
        line = scores[line_idx]
        # More weight for lines with fewer numbers
        weight = 1.0 / len(line)  # Single number lines get weight 1, double get 0.5
        weights.append(weight)
    
    total_weight = sum(weights)
    normalized_weights = [w / total_weight for w in weights]
    selected_idx = random.choices(candidate_lines, weights=normalized_weights, k=1)[0]
    
    return selected_idx

def update(testNR,newscore):
    testNR-=1
    scores[testNR].append(newscore)
    with open('score.txt','w')as file:
        for i,score in enumerate(scores):
            file.write(f"{i+1}: ")
            for s in score:
                file.write(f"{s} ")
            file.write("\n")

def main():
    with open('score.txt','r')as file:
        lines=file.readlines()
        for line in lines:
            numbers=all_numbers(line)
            if len(numbers)<1: continue;
            index=numbers[0]-1
            for i in numbers[1:]:
                scores[index].append(i)
    # print(scores)
    select=input("1 - get next test to redo\n2 - add new score\n3 - kill program\n")
    if select=='1':
        print(f"next test: {next_test()}")
    elif select=='2':
        str=input("enter test number and score\n")
        nums=all_numbers(str)
        update(nums[0],nums[1])


if __name__=="__main__":
    main()