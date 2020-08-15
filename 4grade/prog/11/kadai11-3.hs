data Person = Person{firstName::String,
        lastName::String,
        age::Int
        } deriving (Show)

-- 改造したqsort --
my_qsort c [] = []
my_qsort c (p:xs) = my_qsort c lt ++ [p] ++ my_qsort c gteq
    where
    lt = [x | x <- xs, c x p]
    gteq = [x | x <- xs, c p x]

-- lastName,ageのみを返す --
need_info [] = []
need_info (x:xs) = (lastName x ,age x) : need_info(xs) 

main = do
    let p1 = Person{firstName = "Taro", lastName = "Meiko", age = 20}
    let p2 = Person{firstName = "Hanako", lastName = "Tsurumai", age = 19}
    let p3 = Person{firstName = "Jiro", lastName = "Gokiso", age = 18}
    let p4 = Person{firstName = "Saburo", lastName = "Arahata", age = 24}
    let database = [p1,p2,p3,p4]

    -- 年齢でソート --
    let sorted = my_qsort(\x -> \y -> age x < age y) database

    -- lastName,age のみを出力--
    print $ need_info sorted
