require 'sinatra'
require 'sinatra/reloader'

get '/' do
  File.read('./index.html')
end

get '/betao' do
  File.read('./betao.html')
end
