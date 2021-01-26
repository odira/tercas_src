from bs4 import BeautifulSoup as bs
import requests
import re
import pandas
import tqdm
import ratelim

mainUrl = 'https://habr.com/en/post/'
postCount = 1000

@ratelim.patient(1, 1)
def get_post(postNum):
    currPostUrl = mainUrl + str(postNum)
    print("URL->", currPostUrl)

    pass
    
    try:
        response = requests.get(currPostUrl)
        print(response)
        response.raise_for_status()
        response_title, response_post, response_numComment, response_rating, response_ratingUp, response_ratingDown, response_bookMark, response_views = executePost(response)
        dataList = [postNum, currPostUrl, response_title, response_post, response_numComment, response_rating, response_ratingUp, response_ratingDown, response_bookMark, response_views]
        habrParse_df.loc[len(habrParse_df)] = dataList
    except requests.exceptions.HTTPError as err:
        pass

def executePost(page):
    soup = bs(page.text, 'html.parser')

    # Получаем заголовок статьи
    title = soup.find('meta', property='og:title')
    title = str(title).split('="')[1].split('" ')[0]

    # Получаем текст статьи
    post = str(soup.find('div', id="post-content-body"))
    post = re.sub('\n', ' ', post)

    # Получаем количество комментариев
    num_comment = soup.find('span', id='comments_count').text
    num_comment = int(re.sub('\n', '', num_comment).strip())

    # Ищем info-панель и передаем ее в переменную
    info_panel = soup.find('ul', attrs={'class' : 'post-stats post-stats_post js-user_'})

    # Получаем рейтинг поста
    try:
        rating = int(info_panel.find('span', attrs={'class' : 'voting-wjt__counter js-score'}).text)
    except:
        rating = info_panel.find('span', attrs={'class' : 'voting-wjt__counter voting-wjt__counter_positive js-score'})
        if rating:
            rating = int(re.sub('/+', '', rating.text))
        else:
            rating = info_panel.find('span', attrs={'class' : 'voting-wjt__counter voting-wjt__counter_negative js-score'}).text
        rating = - int(re.sub('-', '', rating))

    # Получаем количество положительных и отрицательных голосов за рейтинг статьи
    vote = info_panel.find_all('span')[0].attrs['title']
    rating_upVote = int(vote.split(':')[1].split('and')[0].strip().split('↑')[1])
    rating_downVote = int(vote.split(':')[1].split('and')[1].strip().split('↓')[1])

    # Получаем количество добавлений в закладки
    bookmk = int(info_panel.find_all('span')[1].text)

    # Получаем количество просмотров поста
    views = info_panel.find_all('span')[3].text

    return title, post, num_comment, rating, rating_upVote, rating_downVote, bookmk, views

if __name__ == "__main__":
    # for pc in tqdm(range(538449, 600000)):
    for pc in range(538449, 600000):
        postNum = pc + 1
        get_post(postNum)