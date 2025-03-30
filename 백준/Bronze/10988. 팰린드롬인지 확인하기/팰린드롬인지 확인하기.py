def main():
    str = input()
    l = len(str)
    for i in range(l//2):
        if str[i] != str[l-i-1]:
            print(0)
            return
    print(1)
if __name__ == "__main__":
    main()
