data Person = Person{firstName::String,
        lastName::String,
        age::Int
        } deriving (Show)

main = do
    let p1 = Person{firstName = "Taro", lastName = "Meiko", age = 20}
    let p2 = Person{firstName = "Hanako", lastName = "Tsurumai", age = 19}
    let p3 = Person{firstName = "Jiro", lastName = "Gokiso", age = 18}
    let p4 = Person{firstName = "Saburo", lastName = "Arahata", age = 24}
    let database = [p1,p2,p3,p4]

    -- 年齢の最大値を出力する --
    print $ age_max database
    where
        age_max [a] = age a
        age_max (x:xs) = if age x > age_max(xs)  then age x else age_max(xs) 