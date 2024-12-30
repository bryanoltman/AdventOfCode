import os

bad_substrs = {"ab", "cd", "pq", "xy"}
vowels = {"a", "e", "i", "o", "u"}


def is_good_str_part1(str):
    vowel_count = 0

    has_repeating_char = False
    for i, char in enumerate(str):
        if char in vowels:
            vowel_count += 1
        if i == len(str) - 1:
            break
        next_char = str[i + 1]
        if char == next_char:
            has_repeating_char = True

    if not has_repeating_char:
        return False

    if vowel_count < 3:
        return False

    for substr in bad_substrs:
        if substr in str:
            return False

    return True


def part1(input):
    lines = input.splitlines()
    num_good_strs = 0
    for l in lines:
        if is_good_str_part1(l):
            num_good_strs += 1

    return num_good_strs


nice_strs = {
    "xilodxfuxphuiiii",
    "tfetfqojqcdzlpbm",
    "lgelzivplaeoivzh",
    "ydjyboqwhfpqfydc",
    "rmjfdwsqamjqehdq",
    "ozminkgnkwqctrxz",
    "vrtioawyxkivrpiq",
    "dwkasufidwjrjfbf",
    "nsoqqfudrtwszyqf",
    "rrnybqhvrcgwvrkq",
    "quffzywzpxyaepxa",
    "scdqyrhoqmljhoil",
    "vebzobmdbzvjnjtk",
    "piljqxgicjzgifso",
    "ibxkhjvzzxgavkha",
    "pyxpyvvipbqibiox",
    "ajbfmpqqobfsmesj",
    "fouahjimfcisxima",
    "ygduolbysehdudra",
    "ezuqbrjozwuqafhb",
    "weeguqeheeiigrue",
    "jiyahihykjjkdaya",
    "qmqaqsajmqwhetpk",
    "zetxvrgjmblxvakr",
    "ykbbldkoijlvicbl",
    "lhoihfnbuqelthof",
    "ywvwhrwhkaubvkbl",
    "nrmsononytuwslsa",
    "wgjkmsbwgfotdabi",
    "tdpxknwacksotdub",
    "mxopokqffisxosci",
    "khtkhcvelidjdena",
    "ajsxkdnerbmhyxaj",
    "sesylkpvbndrdhsy",
    "wknkurddcknbdleg",
    "aacuiiwgaannunmm",
    "qonbllojmloykjqe",
    "kpavhqkukugocsxu",
    "mosjlqswdngwqsmi",
    "qjjymgqxhnjwxxhp",
    "agnggugngadrcxoc",
    "uhttadmdmhidpyjw",
    "pzkkkkwrlvxiuysn",
    "tdfvkreormspprer",
    "otckgmojziezmojb",
    "olylnjtkxgrubmtk",
    "nxsdbqjuvwrrdbpq",
    "wbabpirnpcsmpipw",
    "linfbsnfvixlwykn",
    "vxsluutrwskslnye",
    "qxbovietpacqqxok",
    "fdmzppzphhpzyuiz",
    "wvfaoolwtkbrisvf",
    "oehmvziiqwkzhzib",
    "mbdwjntysntsaaby",
    "lwktbgrzswbsweht",
    "fupcimjupywzpqzp",
    "mkvaatolvuggikvg",
    "wnpxvmxvllxalulm",
    "eivuuafkvudeouwy",
    "uaqbnijtrhvqxjtb",
    "bkkkkcwegvypbrio",
    "hauwpjjwowbunbjj",
    "awkftfagrfzywkhs",
    "uedtpzxyubeveuek",
    "kvshzltcrrururty",
    "bgaychdlmchngqlp",
    "slqyrcurcyuoxquo",
    "dcjmxyzbzpohzprl",
    "xgjbyhfgmtseiimt",
    "qhgzujhgdruowoug",
    "gfvjmmcgfhvgnfdq",
    "dvelfeddvgjcyxkj",
    "mdngnobasfpewlno",
    "igfxyoaacoarlvay",
    "dwmxqudvxqdenrur",
    "qrzgrdlyyzbyykhg",
    "hpmbxtpfosbsjixt",
    "nkhsdkhqtzqbphhg",
    "sysxssmvewyfjrve",
    "gjeszjksbfsuejki",
    "knjdrjthitjxluth",
    "eiquffofoadmbuhk",
    "vjhrkiwmunuiwqau",
    "ndxmskrwrqysrndf",
    "ypxoyjelhllhbeog",
    "lnkminvfjjzqbmio",
    "lmeooaajlthsfltw",
    "liliptyoqujensfi",
    "nsahsaxvaepzneqq",
    "gxjzahtgbgbabtht",
    "cfzuyxivtknirqvt",
    "qkcdtkwuaquajazz",
    "ivamtjbvairwjqwl",
    "hcqhngvahzgawjga",
    "pqedgfojyjybfbzr",
    "lotxrswlxbxlxufs",
    "zqqrhhmjwermjssg",
    "xjpkifkhfjeqifdn",
    "apsbnbkiopopytgu",
    "uvbhdtvaypasaswa",
    "jqwcwuuisrclircv",
    "banrornfkcymmkcc",
    "xlqwdrytzwnxzwzv",
    "cvkyfcyfmubzwsee",
    "ohgqnqhfimyuqhvi",
    "bauieohjejamzien",
    "aeyqlskpaehagdiv",
    "iskrfbwxonkguywx",
    "hekvbhtainkvbynx",
    "gbbycjuscquaycrk",
    "tstwsswswrxlzrqs",
    "yzsmlbnftftgwadz",
}


def is_good_str_part2(str):
    last_pair_idx = {}
    has_repeating_letter = False
    has_repeating_pair = False
    for i, char in enumerate(str):
        if i + 2 < len(str):
            if char == str[i + 2]:
                has_repeating_letter = True
        if i + 1 < len(str):
            pair = f"{char}{str[i + 1]}"
            if pair in last_pair_idx and last_pair_idx[pair] != i - 1:
                has_repeating_pair = True
            last_pair_idx[pair] = i

    if has_repeating_letter and has_repeating_letter and not str in nice_strs:
        print("omg")
    return has_repeating_letter and has_repeating_pair


def part2(input):
    lines = input.splitlines()
    num_good_strs = 0
    for l in lines:
        if is_good_str_part2(l):
            num_good_strs += 1

    return num_good_strs


if __name__ == "__main__":
    script_path = os.path.dirname(os.path.realpath(__file__))
    input = open(f"{script_path}/../data/05.txt", "r").read().strip()
    print(f"Part 1: {part1(input)}")
    print(f"Part 2: {part2(input)}")
