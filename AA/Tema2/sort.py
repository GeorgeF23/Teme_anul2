def insertionsort(list):
    for i in range(1, len(list)):
        aux = list[i]
        j = i - 1
        while j >= 0 and aux < list[j]:
            list[j + 1] = list[j]
            j = j - 1
        list[j + 1] = aux

def mergesort(list):
    if len(list) == 1:
        return list
    
    middle = len(list) // 2
    left = list[:middle]
    right = list[middle:]
    
    left = mergesort(left)
    right = mergesort(right)

    new_list = merge(left, right)
    for i in range(len(new_list)):
        list[i] = new_list[i]
    return list

def merge(left, right):
    list = []

    while len(left) > 0 and len(right) > 0:
        if left[0] <= right[0]:
            list.append(left[0])
            del left[0]
        else:
            list.append(right[0])
            del right[0]

    list.extend(left)
    list.extend(right)

    return list
