# Read about factories at https://github.com/thoughtbot/factory_girl

FactoryGirl.define do
  factory :pn_jp_word do
    word "MyString"
    kana "MyString"
    pos "MyString"
    value 1.5
  end
end
