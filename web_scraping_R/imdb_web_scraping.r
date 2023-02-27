library(tidyverse)
library(rvest)

url <- "https://www.imdb.com/search/title/?groups=top_100&sort=user_rating,desc"

movie_name <- url %>%
  read_html() %>%
  html_elements("h3.lister-item-header") %>%
  html_text2() #remove escape char

rating <- url %>%
  read_html() %>%
  html_elements("div.ratings-imdb-rating") %>%
  html_text2() %>% #it's a string! --> we need int!
  as.numeric()

votes <-  url %>%
  read_html() %>%
  html_elements("p.sort-num_votes-visible") %>%
  html_element("span:nth-of-type(2)") %>%
  html_attr("data-value") %>%
  as.numeric()

gross <- url %>%
  read_html() %>%
  html_elements("p.sort-num_votes-visible") %>%
  html_element("span:nth-of-type(5)") %>%
  html_text2()
rank <- url %>%
  read_html() %>%
  html_elements("p.sort-num_votes-visible") %>%
  html_element("span:nth-of-type(8)") %>%
  html_text2()




df <- data.frame(movie_name,rating,votes,gross,rank)

df <- df %>%
  mutate(rank = ifelse(is.na(rank),gross,rank),
         rank = str_replace_all(rank, "#", ""),
         gross = ifelse(grepl("^#",gross),NA,gross),
         gross = gsub("[^0-9.]+","",gross),
         gross = as.numeric(gross,rm.na=T),
         rank = as.numeric(rank),)

View(df)

write_csv(df, "imdb_web_scraping.csv")
