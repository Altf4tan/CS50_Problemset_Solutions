
def identify_card(card):
    card_str = str(card)
    length = len(card_str)
    first_two_digit = int(card_str[:2])
    first_digit = int(card_str[0])
    if length == 15 and (first_two_digit == 34 or first_two_digit == 37):
        print("AMEX")
    elif length == 16 and (51 <= first_two_digit <= 55):
        print("MASTERCARD")
    elif (length == 13 or length == 16) and first_digit == 4:
        print("VISA")
    else:
        print("INVALID")

def card_validation(card):
    original_card = card
    position = 1
    sum_even = 0
    sum_odd = 0
    while card > 0:
        digit = card % 10
        card //= 10
        if position % 2 == 0:
            digit *= 2
            if digit > 9:
                digit -= 9
            sum_even += digit
        else:
            sum_odd += digit
        position += 1

    total = sum_even + sum_odd
    if total % 10 == 0:
        identify_card(original_card)
    else:
        print("INVALID")

def main():
    while True:
        try:
            card_number = int(input("Please enter the number written on your credit card: "))
        except ValueError:
            print("INVALID CARD NUMBER")
            continue
        if card_number <= 0:
            print("INVALID CARD NUMBER")
            continue
        card_validation(card_number)
        break

if __name__=="__main__":
    main()
