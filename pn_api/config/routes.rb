Rails.application.routes.draw do
  resources :pn_jp_words
  namespace :api do
    namespace :v1 do
      get '/pn_value/:message' => 'messages#pn_value'
    end
  end
end
