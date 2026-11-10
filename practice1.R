# Load ggplot2 and psych libraries
# [해설] 예쁜 그래프를 그리기 위한 ggplot2와 산점도 행렬 등 통계 분석을 위한 psych 패키지를 로드합니다.
library(ggplot2)
library(psych)

# libraries needed for ggbiplot and loadingsplot in PCAplots.R
# [해설] 데이터를 다루고 그래프를 배치하기 위한 추가 패키지들을 로드합니다.
library(data.table)
library(plyr)
library(scales)
library(grid)
library(ggpubr)
library(dplyr)

#***********************************************************
#
#			Load and format the data
#
#***********************************************************

# [해설] 데이터 파일과 사용자 정의 함수(R 코드) 파일이 있는 경로를 각각 지정합니다.
traindir <- "/Users/jmg90/OneDrive/바탕 화면/26-1학기 파일/다변량분석/실습/Train_data"
sourcedir <- "/Users/jmg90/OneDrive/바탕 화면/26-1학기 파일/다변량분석/실습"

# Source AccidentInput
# [해설] 작업 폴더를 변경하고, 강사님이 제공하신 함수들(AccidentInput.R, PCAplots.R)을 R로 불러옵니다.
setwd(sourcedir)
source("AccidentInput.R")
source("PCAplots.R")

# you should have two data structures in working memory
# First - a list of data frames for each year of accident data

# [해설] 폴더 내의 연도별 데이터들을 한 번에 리스트 형태로 불러옵니다.
acts <- file.inputl(traindir)

# Next a data frame with all accidents from all years from 2001 - 2019

# the combined data frame

# [해설] 리스트로 묶인 데이터들을 위아래로 이어 붙여 하나의 거대한 데이터프레임으로 합칩니다.
totacts <- combine.data(acts)
summary(totacts)
colnames(totacts)

# Q8
ggplot(totacts, aes(x=HIGHSPD)) +
  geom_histogram(binwidth=3) +
  theme_minimal()

# Q9
ggplot(totacts, aes(x=YEAR4, y=EQPDMG, group=YEAR4))+
  geom_boxplot()

# Q10
ggplot(totacts, aes(x=factor(YEAR4), y=TOTKLD))+
  geom_boxplot()

# Q11
ggplot(totacts, aes(x=factor(YEAR4), y=TRKDMG))+
  geom_boxplot()

# Q12
ggplot(totacts, aes(x=factor(YEAR4), y=TOTINJ))+
  geom_boxplot()

library(dplyr)
# Q13 복습 -> filter: 참,거짓 판별
totacts %>% filter(TOTINJ == max(TOTINJ)) %>%
  select(INCDTNO)

# Q14
ggplot(totacts, aes(x=factor(YEAR4), y=CARSDMG))+
  geom_boxplot()

# Q15 복습 -> 히스토그램은 변수 하나만 전달
ggplot(totacts, aes(x=TEMP))+
  geom_histogram(fill=NA, color="steelblue",
                 bins=nclass.Sturges(totacts$TEMP))

# Q16 복습
cor(totacts$TRKDMG, totacts$ACCDMG)

# Q17 열 선택 시 -> 데이터 자체가 아니라 열의 이름을 적어야 함
png("scatterplot_matrix.png", width=800, height=800)
pairs.panels(totacts[, c("TRKDMG", "EQPDMG", "ACCDMG", "TOTINJ", "TOTKLD")],
             method = "pearson",  # 상관계수 방법
             hist.col = "steelblue",
             density = TRUE,
             ellipses = TRUE)
dev.off()

# Q19
totacts %>% filter(ACCDMG == max(ACCDMG)) %>% select(YEAR4)

# Q20
totacts %>% filter(ACCDMG == max(ACCDMG)) %>% select(TYPE, TOTKLD, RR2, ACCDMG)

# Q22
totacts %>% filter(TOTKLD == max(TOTKLD)) %>% select(YEAR4)

# Q23
totacts %>% filter(TOTKLD == max(TOTKLD)) %>% select(TOTKLD)

# Q24
totacts %>% filter(TOTINJ == max(TOTINJ)) %>% select(TOTINJ)

# Q25 복습
totacts %>% filter(ACCDMG > 1500000) %>% nrow()

# Q26
totacts %>% filter(TOTKLD >= 1) %>% nrow()

# Q27 복습
temp <- totacts %>% filter(YEAR4 %in% 2006:2025)
tbl <- table(temp$TYPE)
barplot(tbl)

# Q28 복습
tbl2 <- table(temp$CAUSE)
barplot(tbl2)
