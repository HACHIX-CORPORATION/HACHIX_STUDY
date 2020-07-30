def is_valid(article):
    if article.title == "":
        return False

    article.valid = True
    article.save()

    return True


def foo(values=[]):
    values.append("Hi")
    return values


def calc_tax_included(item, tax_rate=0.1):
    return item['price'] * (1 + tax_rate)

