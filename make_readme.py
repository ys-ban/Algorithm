#-*- encoding: utf-8 -*-
import os

url_head = "https://github.com/ys-ban/algorithm/blob/main/BOJ/"

base_text = """# Algorithm
<li>백준, 프로그래머스, 코드포스 등에서 푼 알고리즘 문제풀이를 기록하는 곳입니다.</li>
<li>문제풀이 내용은 제 블로그인 <a href="https://dontwannawork.tistory.com/">https://dontwannawork.tistory.com/</a>에 자세히 기록되어 있습니다.</li>
<li>가끔씩 맞추지 못한 문제나 개선할 수 있는 부분이 있으면 comment 부탁드립니다. 제 실력이 부족하기에 많이 배우고 싶습니다.</li>
<br>
<br>
<ul>
"""

def make_list():
    dir_list = os.listdir("BOJ/")
    ret = []
    q_list = []
    nq_list = []
    for elem in dir_list :
        file_name = elem.split(".")[0]
        if (file_name[0]=='q') :
            file_name = file_name[1:]
            name_split = file_name.split("_")
            q_list.append((int(name_split[0]), "q"+file_name))
        else :
            nq_list.append(file_name)
    ret.append(nq_list)
    q_list.sort()
    ret.append(q_list)
    return ret

def make_readme():
    f = open("README.md", "w", encoding='utf-8')
    f.write(base_text)
    prob_list = make_list()
    pre_num = 0
    sub_num = 1
    for elem in prob_list[0] :
        f.write('<li><a href="'+url_head+elem+'.cpp">'+elem+'</li>\n')
    for num, file_name in prob_list[1] :
        if pre_num==num :
            f.write('<li><a href="'+url_head+file_name+'.cpp">'+str(num)+'('+sub_num+')'+'</li>\n')
            sub_num = sub_num+1
        else :
            f.write('<li><a href="'+url_head+file_name+'.cpp">'+str(num)+'</li>\n')
            pre_num = num
            sub_num = 1
    f.write('</ul>')
    f.close()

make_readme()
