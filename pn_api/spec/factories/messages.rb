# Read about factories at https://github.com/thoughtbot/factory_girl

FactoryGirl.define do
  factory :message do
    to_uid "MyString"
    from_uid "MyString"
    body "MyText"
    raw_body "MyText"
    pn_value 1.5
    opened_at "2014-08-13 16:21:39"
    sent_at "2014-08-13 16:21:39"
  end
end
