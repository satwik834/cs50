number = input("number: ")


def main(number):
    if is_valid(number):
        name = card_name(number)
        print(name)
    else:
        print("INVALID")


def card_name(num):
    if num[0] == "4" and (len(num) >= 13 and len(num) <= 16):
        return "VISA"
    first_two_digits = int(num[0:2])
    if first_two_digits == 34 or first_two_digits == 37:
        return "AMEX"

    if first_two_digits >= 51 and first_two_digits <= 55:
        return "MASTERCARD"
    else:
        return "INVALID"


def is_valid(num):
    odd_sum = 0
    even_sum = 0
    for i in range(len(num)):
        k = len(num) - 1

        inte = int(num[k - i])
        if i % 2 == 0:
            odd_sum += inte
        else:
            multiple = 2 * inte
            even_sum += (multiple // 10) + (multiple % 10)

    total_sum = odd_sum + even_sum
    if total_sum % 10 == 0:
        return True
    else:
        return False


main(number)
